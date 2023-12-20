/**
 * @file AnimatedText.h
 * @author gymna
 *
 * Class that constructs animated texts
 */

#ifndef PROJECT1_SUDOKULIB_ANIMATEDTEXT_H
#define PROJECT1_SUDOKULIB_ANIMATEDTEXT_H

class Game;

/**
 * Class that constructs animated texts
 */
class AnimatedText
{
private:
    /// The game the text is displayed in
    Game *mGame;

    /// The phrase to display
    std::string mPhrase;

    /// The AnimatedText box col position in tiles
    double mCol;

    /// This AnimatedText box row position in tiles
    double mRow;

    /// If the text box should be drawn
    bool mDrawText = false;

public:
    /// Default Constructor (disabled)
    AnimatedText() = delete;

    /**
     * Returns if there is currently a text box on screen
     * @return true if there is a text box on screen
     */
    bool GetDrawText() {return mDrawText;}

    AnimatedText(Game *game, std::string phrase);

    void Reset(std::string newPhrase);

    void Update(double elapsed);

    void Draw(std::shared_ptr<wxGraphicsContext> dc);
};

#endif //PROJECT1_SUDOKULIB_ANIMATEDTEXT_H
