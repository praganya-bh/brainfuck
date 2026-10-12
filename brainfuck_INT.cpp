#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include<vector>
#include<cstdint>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <file.bf>\n"; 
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file)
    {
        std::cerr << "Could not open " << argv[1] << "\n";
        return 1;
    }

    std::string program((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::vector<uint8_t>memory(30000);
    std::vector<size_t>loop_stk;
    std::vector<size_t>jump(program.size());

    for (size_t i = 0; i < program.size(); i++)
    {
        switch(program[i])
        {
            case '[':

                loop_stk.push_back(i);
                break;

            case ']':
            {
                if (loop_stk.empty())
                {
                    std::cerr << "Unmatched ] at position " << i << "\n";
                    return 1;
                }

                size_t open = loop_stk.back();
                loop_stk.pop_back();

                jump[open] = i;
                jump[i] = open;
                
                break;
            }

            default:
                break;
        }
    }

    if (!loop_stk.empty())
    {
        std::cerr << "Loop not closed properly\n";
        return 1;
    }

    size_t ptr = 0;

    for (size_t i = 0; i < program.size(); i++)
    {
        switch(program[i])
        {
            case '>':
                
                ptr = (ptr + 1)%memory.size();
                break;

            case '<':

                ptr = (ptr - 1 + memory.size())%memory.size();
                break;

            case '+':

                memory[ptr]++;
                break;

            case '-':

                memory[ptr]--;
                break;

            case '.':

                std::cout << static_cast<char>(memory[ptr]);
                break;
            case '[':

                if (memory[ptr] == 0)
                {
                    i = jump[i];
                }
               
                break;
            
            case ']':
                
                if (memory[ptr] != 0)
                {
                    i = jump[i];
                }

                break;
            
            case ',':

                memory[ptr] = static_cast<uint8_t>(std::cin.get());
                break;
                
                
        }
    }

    return 0;
}