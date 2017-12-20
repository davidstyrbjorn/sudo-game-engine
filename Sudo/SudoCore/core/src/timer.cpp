#include"../include/utility/timer.h"

namespace sudo { namespace utility { 

	Timer::Timer() {
		m_startedAt = 0;
		m_pausedAt = 0;
		m_paused = false;
		m_started = false;
	}

	bool Timer::IsStarted() {
		return m_started;
	}

	bool Timer::IsStopped() {
		return !m_started;
	}

	bool Timer::IsPaused() {
		return m_paused;
	}

	bool Timer::IsActive() {
		return !m_paused & m_started;
	}

	void Timer::Pause() {
		if (m_paused || !m_started)
			return;

		m_paused = true;
		m_pausedAt = clock();
	}

	void Timer::Resume() {
		if (!m_paused)
			return;

		m_paused = false;
		m_startedAt = clock() - m_pausedAt;
	}

	void Timer::Stop() {
		m_started = false;
	}

	void Timer::Start() {
		if (m_started)
			return;

		m_started = true;
		m_paused = false;
		m_startedAt = clock();
	}

	void Timer::Reset() {
		m_paused = false;
		m_startedAt = clock();
	}

	clock_t Timer::GetTicks()
	{
		if (!m_started)
			return 0;
		if (m_paused)
			return m_pausedAt - m_startedAt;
		return clock() - m_startedAt;
	}

} } 