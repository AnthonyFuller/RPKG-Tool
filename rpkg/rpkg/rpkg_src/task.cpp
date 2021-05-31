#include "task.h"
#include "file.h"
#include "global.h"
#include "util.h"
#include "generic_function.h"
#include "rpkg_function.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void task::execute(std::string& command, std::string& input_path, std::string& filter, std::string& search, std::string& search_type, std::string& output_path)
{
    if (command == "-compute_ioi_hash")
    {
        generic_function::compute_ioi_hash(filter);
    }
    if (command == "-compute_ioi_hash_from_file")
    {
        generic_function::compute_ioi_hash_from_file(input_path);
    }
    else if (command == "-decrypt_packagedefinition_thumbs")
    {
        generic_function::decrypt_packagedefinition_thumbs(input_path, output_path);
    }
    else if (command == "-encrypt_packagedefinition_thumbs")
    {
        generic_function::encrypt_packagedefinition_thumbs(input_path, output_path);
    }
    else if (command == "-extract_from_rpkg")
    {
        rpkg_extraction_vars rpkg_vars;

        rpkg_vars.input_path = input_path;
        rpkg_vars.filter = filter;
        rpkg_vars.output_path = output_path;

        rpkg_function::extract_from_rpkg(rpkg_vars);
    }
    else if (command == "-extract_ores_from")
    {
        rpkg_function::extract_ores_from(input_path, filter, output_path);
    }
    else if (command == "-extract_wwem_to_ogg_from")
    {
        rpkg_function::extract_wwem_to_ogg_from(input_path, filter, output_path);
    }
    else if (command == "-extract_wwes_to_ogg_from")
    {
        rpkg_function::extract_wwes_to_ogg_from(input_path, filter, output_path);
    }
    else if (command == "-extract_wwev_to_ogg_from")
    {
        rpkg_function::extract_wwev_to_ogg_from(input_path, filter, output_path);
    }
    else if (command == "-extract_dlge_to_json_from")
    {
        rpkg_function::extract_dlge_to_json_from(input_path, filter, output_path, false);
    }
    else if (command == "-extract_locr_to_json_from")
    {
        rpkg_function::extract_locr_to_json_from(input_path, filter, output_path, false);
    }
    else if (command == "-extract_rtlv_to_json_from")
    {
        rpkg_function::extract_rtlv_to_json_from(input_path, filter, output_path, false);
    }
    else if (command == "-generate_rpkg_from")
    {
        rpkg_function::generate_rpkg_from(input_path, filter,output_path);
    }
    else if (command == "-hash_depends")
    {
        rpkg_function::hash_depends(input_path, filter, output_path);
    }
    else if (command == "-hash_probe")
    {
        rpkg_function::hash_probe(input_path, filter, output_path);
    }
    else if (command == "-hash_probe_from_file")
    {
        rpkg_function::hash_probe_from_file(input_path, filter, output_path);
    }
    else if (command == "-import_rpkg")
    {
        rpkg_function::import_rpkg(input_path);
    }
    else if (command == "-rebuild_wwev_in")
    {
        rpkg_function::rebuild_wwev_in(input_path, filter, output_path);
    }
    else if (command == "-rebuild_dlge_from_json_from")
    {
        rpkg_function::rebuild_dlge_from_json_from(input_path, filter, output_path);
    }
    else if (command == "-rebuild_locr_from_json_from")
    {
        rpkg_function::rebuild_locr_from_json_from(input_path, filter, output_path);
    }
    else if (command == "-rebuild_rtlv_from_json_from")
    {
        rpkg_function::rebuild_rtlv_from_json_from(input_path, filter, output_path);
    }
    else if (command == "-rpkg_command_json")
    {
        generic_function::command_json(input_path);
    }
    else if (command == "-search_rpkg")
    {
        rpkg_extraction_vars rpkg_vars;

        rpkg_vars.input_path = input_path;
        rpkg_vars.filter = filter;
        rpkg_vars.search = search;
        rpkg_vars.search_type = search_type;
        rpkg_vars.output_path = output_path;
        rpkg_vars.search_mode = true;

        rpkg_function::extract_from_rpkg(rpkg_vars);
    }
}

void task::process_and_execute_files_draged_and_dropped(std::vector<std::string>& dragged_and_dropped_files)
{
    for (int i = 0; i < dragged_and_dropped_files.size(); i++)
    {
        if (file::is_json_file(dragged_and_dropped_files.at(i)))
        {
            std::string command = "-rpkg_command_json";
            std::string empty = "";

            task::execute(command, dragged_and_dropped_files.at(i), empty, empty, empty, empty);
        }
        else if (file::is_rpkg_file(dragged_and_dropped_files.at(i)))
        {
            std::string command = "-extract_from_rpkg";
            std::string empty = "";

            task::execute(command, dragged_and_dropped_files.at(i), empty, empty, empty, empty);
        }
    }
}

void task::process_and_execute_command_line_args(std::vector<std::vector<std::string>>& commands)
{
    std::string command = "";
    std::string input_path = "";
    std::string filter = "";
    std::string search = "";
    std::string search_type = "";
    std::string output_path = "";
    std::vector<std::string> commands_without_paths = { "-compute_ioi_hash" };
    std::vector<std::string> commands_with_paths = { "-compute_ioi_hash_from_file",
                                                     "-decrypt_packagedefinition_thumbs",
                                                     "-encrypt_packagedefinition_thumbs",
                                                     "-extract_from_rpkg",
                                                     "-extract_ores_from",
                                                     "-extract_wwem_to_ogg_from",
                                                     "-extract_wwes_to_ogg_from",
                                                     "-extract_wwev_to_ogg_from",
                                                     "-extract_dlge_to_json_from",
                                                     "-extract_locr_to_json_from",
                                                     "-extract_rtlv_to_json_from",
                                                     "-generate_rpkg_from",
                                                     "-hash_depends",
                                                     "-hash_probe",
                                                     "-hash_probe_from_file",
                                                     "-rebuild_wwev_in",
                                                     "-rebuild_dlge_from_json_from",
                                                     "-rebuild_locr_from_json_from",
                                                     "-rebuild_rtlv_from_json_from",
                                                     "-rpkg_command_json",
                                                     "-search_rpkg" };

    int command_count = 0;

    for (int i = 0; i < commands.size(); i++)
    {
        if (std::find(commands_with_paths.begin(), commands_with_paths.end(), commands.at(i).at(0)) != commands_with_paths.end())
        {
            command = commands.at(i).at(0);
            input_path = commands.at(i).at(1);
            command_count++;
        }
        else if (std::find(commands_without_paths.begin(), commands_without_paths.end(), commands.at(i).at(0)) != commands_without_paths.end())
        {
            command = commands.at(i).at(0);
            filter = commands.at(i).at(1);
            command_count++;
        }
        else if (util::to_lower_case(commands.at(i).at(0)) == "-text_search")
        {
            search_type = "text";
            search = commands.at(i).at(1);
        }
        else if (util::to_lower_case(commands.at(i).at(0)) == "-hex_search")
        {
            search_type = "hex";
            search = commands.at(i).at(1);
        }
        else if (util::to_lower_case(commands.at(i).at(0)) == "-regex_search")
        {
            search_type = "regex";
            search = commands.at(i).at(1);
        }
        else if (util::to_lower_case(commands.at(i).at(0)) == "-filter")
        {
            filter = commands.at(i).at(1);
        }
        else if (util::to_lower_case(commands.at(i).at(0)) == "-output_path")
        {
            output_path = commands.at(i).at(1);
        }
        else
        {
            LOG_AND_EXIT("Error: Invalid command in command line.");
        }
    }

    if (command_count > 1)
    {
        LOG_AND_EXIT("Error: Too many commands on the command line.");
    }

    task::execute(command, input_path, filter, search, search_type, output_path);
}