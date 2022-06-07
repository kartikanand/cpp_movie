#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <string>

#include "httplib.h"

std::string get_help_text()
{
    return R""""(
Command line interface
----------------------

Flags
-----
--movie, -m :: [optional]
Movie name to search for

--filter, -f :: [optional] Requires --movie, -m argument
Streaming platform to filter

--help, -h :: [optional] If present with other arguments, then explain that argument
Output help

--verbose, -v :: [optional]
Be verbose while running (TBD)

Examples
--------
cpp_movie --movie <movie_name>
cpp_movie --movie <movie_name> --filter <streaming_platform>
cpp_movie --help
cpp_movie -m <movie_name>
cpp_movie -h
cpp_movie --movie <movie_name> --verbose
cpp_movie --movie <movie_name> -v

Output
------
JSON output with the following keys
{
  "name": "movie name",
  "imdb_rating": "imdb rating",
  "streaming_platforms": ["list of streaming platforms movie is available on"]
})"""";
}

void print_help()
{
    std::cout << get_help_text();
}

std::string get_movie_details(const std::string &movie_name)
{
    httplib::Client cli("https://example.com");

    auto res = cli.Get("/");
    return std::string(res->body);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_help();

        // TODO: return appropriate return code according to error
        return -1;
    }

    bool is_movie_arg = false;
    bool is_streaming_platform_arg = false;
    std::string movie_name;
    std::string streaming_platform;

    // skip the first argument since it's the name of the program
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = std::string(argv[i]);
        bool is_movie_arg = false;

        if (arg == "help" || arg == "-h")
        {
            print_help();
        }
        else if (arg == "movie_name")
        {
            is_movie_arg = true;
        }
        else if (arg == "streaming_platform")
        {
            is_streaming_platform_arg = true;
        }
        else if (is_movie_arg)
        {
            movie_name = arg;
        }
        else if (is_streaming_platform_arg)
        {
            streaming_platform = arg;
        }
        else
        {
            std::cout << "Invalid command. Pass -h, --help to get help" << std::endl;
        }
    }

    if (movie_name.length() == 0)
    {
        std::cout << "No movie name supplied. Pass -h, --help to get help" << std::endl;
    }

    auto movie_details = get_movie_details(movie_name);

    std::cout << movie_details << std::endl;

    return 0;
}
