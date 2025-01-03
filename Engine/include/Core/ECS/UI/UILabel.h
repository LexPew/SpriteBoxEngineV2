#pragma once

#include "UIComponent.h"
#include "TextData.h"

// Class: UILabel
// Purpose: A UI component that renders text.
class UILabel : public UIComponent
{
private:
    TextData textData; // Holds text-related data such as content, font, size, and color.

public:
	UILabel() = default;
    /**
     * @brief Constructor for UILabel.
     * @param p_textData The text data to render.
     */
    UILabel(const TextData& p_textData) : textData(p_textData) {}

    void Start() override{}

    void Update(float p_deltaTime) override{}

	void HandleInput(const Vector2& p_mousePosition, bool p_click) override{}

    /**
     * @brief Renders the UILabel on the screen.
     * @param p_renderer The renderer responsible for drawing the label.
     */
    void Render(Renderer& p_renderer) override;

    /**
     * @brief Sets the text content of the label.
     * @param p_text The new text content.
     */
    void SetText(const std::string& p_text)
    {
        textData.text = p_text;
    }

    /**
     * @brief Sets the font size of the label.
     * @param p_fontSize The new font size.
     */
    void SetFontSize(int p_fontSize)
    {
        textData.fontSize = p_fontSize;
    }

    /**
     * @brief Sets the color of the text.
     * @param p_color The new color for the text.
     */
    void SetColor(const Color4& p_color)
    {
        textData.color = p_color;
    }

    /**
     * @brief Sets the font ID used by the label.
     * @param p_fontId The ID of the font to use.
     */
    void SetFontId(const std::string& p_fontId)
    {
        textData.fontId = p_fontId;
    }

    /**
     * @brief Sets the entire text data for the label.
     * @param p_textData The new text data object.
     */
    void SetTextData(const TextData& p_textData)
    {
        textData = p_textData;
    }

    /**
     * @brief Gets the current text data of the label.
     * @return TextData The current text data.
     */
    TextData GetTextData() const
    {
        return textData;
    }

	template <class Archive>
    void save(Archive& archive) const
    {
        archive(cereal::base_class < UIComponent>(this), textData);
    }
	template <class Archive>
	void load(Archive& archive)
	{
		archive(cereal::base_class < UIComponent>(this), textData);
	}

};

CEREAL_REGISTER_TYPE(UILabel)
CEREAL_REGISTER_POLYMORPHIC_RELATION(UIComponent, UILabel)
