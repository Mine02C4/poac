//
// Summary: Create a new poacpm project.
// Options: <project-name>
//
#ifndef POAC_SUBCMD_NEW_HPP
#define POAC_SUBCMD_NEW_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <map>

#include <boost/filesystem.hpp>

#include "../console.hpp"
#include "../ftemplate.hpp"


namespace poac::subcmd { struct new_ {
    static const std::string summary() { return "Create a new poacpm project."; }
    static const std::string options() { return "<project-name>"; }

    void operator()() { _main(); }

    void _main() {
        namespace fs = boost::filesystem;
        // Check if the ARGMENT directory exists.
        if (const fs::path dir(fs::path(".") / fs::path("deps")); fs::is_directory(dir) && fs::exists(dir)) {
            poac::console::color::red();
            std::cerr << "hogeee" << std::endl;
            poac::console::color::reset();
        }
        else {
            fs::create_directory(dir);
            std::ofstream ofs;
            std::map<fs::path, std::string> file{
                    { ".gitignore", poac::ftemplate::_gitignore },
                    { "main.cpp",   poac::ftemplate::main_cpp },
                    { "poac.lock",  poac::ftemplate::poac_lock },
                    { "poac.yml",   poac::ftemplate::poac_yml },
                    { "README.md",  poac::ftemplate::README_md }
            };
            for ( const auto& [ name, text ] : file ) {
                ofs.open((dir / name).string());
                if (ofs.is_open()) ofs << text;
                ofs.close();
                ofs.clear();
            }
            echo_result("deps");
        }
    }
    void echo_result(std::string_view str) {
        // echo
        // echo "Your \"$1\" project was created successfully."
        // echo
        // echo
        // echo "Go into your project by running:"
        // echo "    $ cd $1"
        // echo
        // echo "Start your project with:"
        // echo "    $ poac install hello_world"
        // echo "    $ poac run main.cpp"
        // echo
    }
};} // end namespace
#endif