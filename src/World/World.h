#ifndef WORLD_H
#define WORLD_H

#include <thread>
#include <atomic>
#include "../Camera.h"
#include "../Player.h"
#include "../Renderers/Renderer.h"
#include "Chunk/ChunkManager.h"

class World
{
    public:
        World(const Camera& cam, Player& player);

		void update();
		void renderWorld(const Camera& cam, Renderer& renderer);

        ~World();
    protected:

    private:
		ChunkManager m_chunkManager;

		void loadChunks(const Camera& cam);

		std::atomic<bool> isRunning{ true };
		std::vector<std::thread> loadThreads;


};

#endif // WORLD_H
