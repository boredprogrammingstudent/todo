#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
class FileHandler
{
private:
    std::vector<std::vector<std::string>> file;
    const std::string PATH = "todo.txt";
    std::vector<std::string> vectorize(const std::string &str)
    {
        std::istringstream iss(str);
        std::string word;
        std::vector<std::string> line{};
        while (iss >> word)
        {
            line.push_back(word);
        }
        return line;
    }

public:
    FileHandler()
    {
        auto in = std::ifstream(PATH);
        file = std::vector<std::vector<std::string>>{};
        if (in)
        {
            std::string str{};
            while (std::getline(in, str))
            {
                file.push_back(vectorize(str));
            }
        }
    }
    std::vector<std::string> *get(int index)
    {
        return &file[index];
    }
    void removeIf(std::function<bool(std::vector<std::string>)> f)
    {
        file.erase(std::remove_if(file.begin(), file.end(), f), file.end());
    }
    void add(const std::string &line)
    {
        file.push_back(vectorize(line));
    }
    void remove(int index)
    {
        file.erase(file.begin() + index);
    }
    void save()
    {
        auto out = std::ofstream(PATH);
        for (int i = 0; i < file.size(); ++i)
        {
            out << file[i][0];
            for (int j = 1; j < file[i].size(); ++j)
            {
                out << " " << file[i][j];
            }
            out << std::endl;
        }
    }
    void print()
    {
        std::cout << std::endl;
        for (int i = 0; i < 15; ++i)
        {
            std::cout << "_";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < file.size(); ++i)
        {
            auto x_it = std::find(file[i].begin(), file[i].end(), "-x");
            if (x_it != file[i].end())
            {
                file[i].erase(x_it);
                std::cout << "\033[9m";
            }
            auto i_it = std::find(file[i].begin(), file[i].end(), "-i");
            if (i_it != file[i].end())
            {
                file[i].erase(i_it);
                std::cout << "\033[91m";
            }
            std::cout << i << "\t";
            for (int j = 0; j < file[i].size(); ++j)
            {
                std::cout << " " << file[i][j];
            }
            std::cout << "\033[0m" << std::endl;
        }
        for (int i = 0; i < 15; ++i)
        {
            std::cout << "_";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    int getLength()
    {
        return file.size();
    }
};
class Todo
{
private:
    FileHandler fh = FileHandler();

public:
    void add(const std::string &line)
    {
        fh.add(line);
        fh.save();
    }
    void important()
    {
        important(fh.getLength() - 1);
    }
    void important(int index)
    {
        auto line = fh.get(index);
        if (std::find(line->begin(), line->end(), "-i") == line->end())
        {
            line->push_back("-i");
        }
        fh.save();
    }
    void cross()
    {
        cross(fh.getLength() - 1);
    }
    void cross(int index)
    {
        auto line = fh.get(index);
        if (std::find(line->begin(), line->end(), "-x") == line->end())
        {
            line->push_back("-x");
        }
        fh.save();
    }
    void remove(int index)
    {
        fh.remove(index);
        fh.save();
    }
    void show()
    {
        fh.print();
    }
    void removeCrossed()
    {
        fh.removeIf([](std::vector<std::string> s) {
            return std::find(s.begin(), s.end(), "-x") != s.end();
        });
        fh.save();
    }
};
bool isCmd(char *cmd, const std::vector<std::string> &nameCalls)
{
    return std::find(nameCalls.begin(), nameCalls.end(), std::string(cmd)) != nameCalls.end();
}
int main(int argc, char *argv[])
{
    auto todo = Todo();

    using calls = std::vector<std::string>;

    if (argc == 1 || isCmd(argv[1], calls{"show", "s"}))
    {
        todo.show();
    }
    else if (isCmd(argv[1], calls{"important", "i"}))
    {
        for (int i = 2; i < argc; ++i)
        {
            todo.important(std::stoi(std::string(argv[i])));
        }
        todo.show();
    }
    else if (isCmd(argv[1], calls{"cross", "x", "c"}))
    {
        for (int i = 2; i < argc; ++i)
        {
            todo.cross(std::stoi(std::string(argv[i])));
        }
        todo.show();
    }
    else if (isCmd(argv[1], calls{"remove", "r", "rm"}))
    {
        std::vector<int> indexes{};
        for (int i = 2; i < argc; ++i)
        {
            indexes.push_back(std::stoi(std::string(argv[i])));
        }
        std::sort(indexes.begin(), indexes.end(), std::greater<int>());
        for (int i = 0; i < indexes.size(); ++i)
        {
            todo.remove(indexes[i]);
        }
        todo.show();
    }
    else if (isCmd(argv[1], calls{"add", "a"}))
    {
        std::string temp{};
        temp += std::string(argv[2]);
        for (int i = 3; i < argc; ++i)
        {
            temp += " " + std::string(argv[i]);
        }
        todo.add(temp);
        todo.show();
    }
    else if (isCmd(argv[1], calls{"rx"}))
    {
        todo.removeCrossed();
        todo.show();
    }
    else
    {
        /*
            this is the default for when you just do
                $ todo eat
            it acts as if it was
                $ todo add eat
            just be careful that your todo doesnt start with a word like "remove" or "cross" if you use this else it wont work
        */

        std::string temp{};
        temp += std::string(argv[1]);
        for (int i = 2; i < argc; ++i)
        {
            temp += " " + std::string(argv[i]);
        }
        todo.add(temp);
        todo.show();
    }
}