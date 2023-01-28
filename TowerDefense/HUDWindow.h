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
		virtual					~HUDWindow();

		template <typename T, typename ... Args>
		T*						AddButton(Vector2 relativePosition, Args... args);
		virtual void			Update();
		void					Clear();
		void					Close() const;
		virtual void			Create() = 0;

	protected:
		RenderTexture			m_windowTexture;
		Sprite*					m_windowSprite;

		const Color				COLOR_TITLE = RAYWHITE;
		const Color				COLOR_DARKENER = ColorAlpha(DARKPURPLE, .75f);

		const int				FONT_SIZE_TITLE = 40;
		const int				FONT_SIZE_CONTENT = 20;
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