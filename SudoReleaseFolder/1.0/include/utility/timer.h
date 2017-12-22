#pragma once

#include<ctime>

/*
* Timer class used for limiting FPS in engine core loop
*/

namespace sudo { namespace utility { 

	class Timer {
	private:
		clock_t m_startedAt, m_pausedAt;
		bool m_paused, m_started;

	public:
		Timer();
		bool IsStarted();
		bool IsStopped();
		bool IsPaused();
		bool IsActive();

		void Pause();
		void Resume();
		void Stop();
		void Start();
		void Reset();

		clock_t GetTicks();
	};

}}