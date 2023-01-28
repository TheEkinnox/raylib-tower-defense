#pragma once
#include <raylib.h>
#include <vector>

namespace TD
{
	class HUDButton;
	class Sprite;

	class HUDWindow
	{
	public:
		std::vector<HUDButton*>	Buttons;
		Vector2					Position;
		Vector2					Dimensions;

		HUDWindow(Vector2 position, Vector2 dimensions);
		~HUDWindow();

		template <typename T, typename ... Args>
		T*						AddButton(Vector2 relativePosition, Args... args);
		void					Update();
		void					Clear();
		virtual void			Create() = 0;

	protected:
		RenderTexture			m_windowTexture;
		Sprite*					m_windowSprite;
	};

	template<typename T, typename ... Args>
	T* HUDWindow::AddButton(Vector2 relativePosition, Args... args)
	{
		if (!std::is_base_of_v<HUDButton, T>)
			return nullptr;

		Buttons.push_back(new T(relativePosition, *this, args...));

		return static_cast<T*>(Buttons.back());
	}
}