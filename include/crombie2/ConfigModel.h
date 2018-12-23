#ifndef CROMBIE2_CONFIG_MODEL_H
#define CROMBIE2_CONFIG_MODEL_H

#include <cstdlib>
#include <list>
#include <string>

#include <crombie2/Types.h>

namespace crombie2 {
  class ConfigModel {

  public:

    /// Get the class name of the configuration object
    virtual std::string get_name () = 0;


    /**
       Loads the configuration from a file
       @param file_name Name of the file that holds the configuration
    */
    void load (const std::string& file_name);


    /**
       Loads the configuration given by a tag
       @param tag The name of the tag
    */
    void load_tag (const std::string& tag);


    /**
       Saves the configuration in a file
       @param file_name Name of the file to save the configuration in
    */
    void save (const std::string& file_name);


    /**
       Hashes configuration and saves in a set location
       @returns The file name where the configuration was saved
    */
    std::string save ();


    /**
       Saves the configuration in a file
       @param tag The name of the tag
    */
    void save_tag (const std::string& tag);


    /**
       Change the location to save the config directories
       @param dir The name of the directory to save everything
    */
    static void set_config_dir (const std::string& dir);


  protected:

    /**
       Loads the configuration from a bunch of strings
       @param config Configuration file after being parsed
    */
    virtual void read (const Types::strings& config) = 0;


    /// Creates a string version of the configuration
    virtual std::list<std::string> serialize () = 0;


  private:

    /// Make a hash of the serialization
    std::string hash ();


    /// The location to save all used configurations
    static std::string config_directory;

  };
}

#endif
