#ifndef CROMBIE2_CONFIG_MODEL_H
#define CROMBIE2_CONFIG_MODEL_H

#include <list>

#include <crombie2/Types.h>

namespace crombie2 {
  /**
     @brief Abstract class that each saveable object should implement
  */
  class ConfigModel {

  public:
    ConfigModel (const std::string& file_name = "");
    virtual ~ConfigModel () = default;


    /// Get the class name of the configuration object
    virtual std::string get_name () const = 0;


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
       @param overwrite Set to true if you definitely want to overwrite tag.
              Otherwise, a prompt is displayed to confirm overwriting.
    */
    void save_tag (const std::string& tag, bool overwrite = false);


    /**
       Change the location to save the config directories
       @param dir The name of the directory to save everything
    */
    static void set_config_dir (const std::string& dir);


    static const std::string& get_config_dir ();


    virtual bool is_valid () const;

  protected:

    /**
       Loads the configuration from a bunch of strings
       @param config Configuration file after being parsed
    */
    virtual void read (const Types::strings& config) = 0;


    /// Creates a string version of the configuration
    virtual std::list<std::string> serialize () const = 0;


  private:

    /// Make a hash of the serialization
    std::string hash ();


    /// The location to save all used configurations
    static std::string config_directory;

  };
}

#endif
