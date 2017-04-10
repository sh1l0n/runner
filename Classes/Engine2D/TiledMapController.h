//
// Created by chancloid on 12/03/2017.
//

#pragma once

#include <unordered_map>
#include "../Engine2D/TiledMap/Chunck.h"
#include "../Engine2D/TiledMap/TiledMapGenerator.hpp"

namespace TiledMap {

    const unsigned char K_NUMBERS_CHUNCKS_MEMORY = 0x03;
    const int K_WORLD_SIZE_PX = (int)(K_WIDTH*K_SIZE_IMAGE_SPRITE*K_FACTOR_SCALE);
    const float K_FLAG_CHUNCK_PART_1 = K_WORLD_SIZE_PX/4.f;
    const float K_FLAG_CHUNCK_PART_2 = (2.f*K_WORLD_SIZE_PX)/4.f;
    const float K_FLAG_CHUNCK_PART_3 = (3.f*K_WORLD_SIZE_PX)/4.f;
    const float K_FLAG_CHUNCK_THRESHOLD = 50;

    struct EnumClassHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    enum ChunckIdentifiers {
        A = 0x00,
        B = 0x01,
        C = 0x02
    };

    template <typename Key>
    using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;
    template <typename Key, typename T>
    using MyUnorderedMap = std::unordered_map<Key, T, HashType<Key>>;


    class TiledMapControllerListener {
        public:
            virtual void removeChunckFromScene(const ChunckIdentifiers id) = 0;
            virtual void addChunckToScene(const ChunckIdentifiers id, Chunck* chunck) = 0;
    };

    class TiledMapController {

        private:
            std::vector<bool> flags;
            unsigned int _numberOfChuncksGenerated;
            unsigned int _globalPosition;
            MyUnorderedMap<ChunckIdentifiers, Chunck*> _chuncks;
            ChunckIdentifiers _currentChunck;
            TiledMapControllerListener* _listener;
            ChunckIdentifiers getNextChunck() const;
            ChunckIdentifiers getLastChunck() const;

        public:
            TiledMapController(TiledMapControllerListener* listener);
            ~TiledMapController();
            void update(const int position);
    };
}
