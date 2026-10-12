#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file.bf>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file)
    {
        std::cerr << "Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::string program((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());


    size_t depth = 0;

    for (size_t i = 0; i < program.size(); i++)
    {
        if (program[i] == '[')
        {
            depth++;
        }
        else if (program[i] == ']')
        {
            if (depth == 0)
            {
                std::cerr << "Unmatched ] at position " << i << "\n";
                return 1;
            }
            
            depth--;
        }
    }

    if (depth != 0)
    {
        std::cerr << "Some [ was never closed" << "\n";
        return 1;
    }


    std::ofstream out("out.c");

    out << "#include <stdio.h>\n";
    out << "int main() {\n";
    out << "    unsigned char memory[30000] = {0};\n";
    out << "    unsigned char *p = memory;\n";

    for (size_t i = 0; i < program.size(); i++)
    {
        switch (program[i])
        {
            case '>':

            {
                size_t x = i+1;

                while(x < program.size() && program[x] == '>')
                {
                    x++;
                }

                out << "    p += " << x-i << ";\n";

                i = x-1;
                break;
            
            }

            case '<':

            {
                size_t x = i+1;

                while(x < program.size() && program[x] == '<')
                {
                    x++;
                }

                out << "    p -= " << x-i << ";\n";

                i = x-1;

                break;
            
            }

            case '+':

            {

                 size_t x = i+1;

                while(x < program.size() && program[x] == '+')
                {
                    x++;
                }

                out << "    *p += " << x-i << ";\n";

                i = x-1;

                break;
            
            }

            case '-':

            {
                size_t x = i+1;

                while(x < program.size() && program[x] == '-')
                {
                    x++;
                }

                out << "    *p -= " << x-i << ";\n";

                i = x-1;

                break;
            
            }

            case '.':
            
            {

                out << "    putchar(*p);\n";
                break;
            
            }

            case ',':

            {

                out << "    *p = getchar();\n";
                break;

            }

            case '[':

            {

                out << "while (*p) {\n";
                break;

            }

            case ']':

            {
                out << "}\n";
                break;
            
            }

        }
    }

    out << "    return 0;\n";
    out << "}\n";

    return 0;
}