#pragma once

#include<ctime>

namespace sudo { namespace utility { 

	class Timer {
	private:
		clock_t m_startedAt, m_pausedAt;
		bool m_paused, m_started;

	public:
		Timer();

		// Getters
		bool IsStarted();
		bool IsStopped();
		bool IsPaused();
		bool IsActive();
		clock_t GetTicks(); // typedef long

		// State modifications
		void Pause();
		void Resume();
		void Stop();
		void Start();
		void Reset();

	};

}}