#ifndef MAEDN_CLASS_EXPORT_IMPORT_HPP
#define MAEDN_CLASS_EXPORT_IMPORT_HPP

// Helper to load and write file for game state

#include "CppStructsForConfigAndState.hpp"

namespace maednhelper
{
    /**
     * Use to write current game configuration and state to a file. Does not overwrite existing files. May throw exceptions
     */
    void saveFile(std::shared_ptr<GameConfig> config, std::shared_ptr<GameState> state);

    /**
     * Use to load game configuration and state from a file. May throw exceptions
     */
    bool loadFile(std::string fileName, std::shared_ptr<GameConfig> config, std::shared_ptr<GameState> state);
}
#endif