#pragma once
#include "Core/Event.h"

namespace Bit {

	class ImGuiSys
	{
	public:
		ImGuiSys();
		~ImGuiSys() = default;

		void Init();
		void Shutdown();
		void OnEvent(Event& e);

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}