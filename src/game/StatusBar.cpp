#include "StatusBar.hpp"
#include <list>
//needed for gcc
#include <algorithm>
#include "FontRender.hpp"


using std::cout;
using std::endl;
using std::list;
using std::string;

namespace jumper {

    const int StatusBar::m_maxScore = 1000000;


    StatusBar::StatusBar(SDL_Renderer *renderer,
                         SDL_Texture *texture,
                         int tileWidth,
                         int tileHeight,
                         int capitalOffset,
                         int minusculeOffset,
                         int numberOffset,
                         int letterCount,
                         int offsetMiddle)
            : FontRender(tileHeight, tileWidth, renderer, texture) {
        m_score = 0;
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
        m_capitalOffset = capitalOffset;
        m_minusculeOffset = minusculeOffset;
        m_numberOffset = numberOffset;
        m_letterCount = letterCount;
        m_offsetMiddle = offsetMiddle;
        m_weaponChanged = false;
    }


    void StatusBar::setScore(int score) {
        if (score < m_maxScore) {
            m_score = score;
        }
        else {
            m_score = m_maxScore;
        }
    }

    int StatusBar::getScore() const {
        return m_score;
    }

    void StatusBar::render() {
        SDL_Rect target;
        SDL_Rect source;


        //Paint the Border in Red
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 1);
        //left line
        SDL_RenderDrawLine(m_renderer,
                           m_startPosition.x(),
                           m_startPosition.y(),
                           m_startPosition.x(),
                           m_startPosition.y() - m_startPosition.y());
        //Buttom line
        SDL_RenderDrawLine(m_renderer,
                           m_endPosition.x(),
                           m_startPosition.y(),
                           m_startPosition.x(),
                           m_startPosition.y());
        //Top line
        SDL_RenderDrawLine(m_renderer,
                           m_endPosition.x(),
                           m_endPosition.y(),
                           m_startPosition.x(),
                           m_endPosition.y());
        //Right line
        SDL_RenderDrawLine(m_renderer,
                           m_endPosition.x(),
                           m_endPosition.y(),
                           m_endPosition.x(),
                           m_startPosition.y());

        //Make the Background black
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 1);
        target.w = m_tileWidth;
        target.h = m_tileHeight;
        source.w = target.w;
        source.h = target.h;

        //Render Score
        displayNumber(m_score, m_scorePosition, source, target);

        //Render Weapon
        if (m_weaponChanged) {
            m_weaponSource.clear();
            vector<Vector2i> weapon_source = renderString(m_weaponName,
                                                          m_minusculeOffset,
                                                          m_capitalOffset,
                                                          m_numberOffset);
            setWeaponPosition(Vector2i(m_weaponPosition.x() - (((m_weaponName.length() + 2) / 2) * m_tileWidth),
                                       m_horziontalAlignemnt));
            for (int i = 0; i < weapon_source.size(); i++) {
                source.x = weapon_source[i].x();
                source.y = weapon_source[i].y();
                m_weaponSource.push_back(source);

                target.x = m_weaponPosition.x() + (i * m_tileWidth) + i;
                target.y = m_weaponPosition.y();
                m_weaponTarget.push_back(target);
                SDL_RenderCopy(m_renderer, m_texture, &source, &target);
            }
        } else {
            for (int i = 0; i < m_weaponSource.size(); i++) {
                SDL_RenderCopy(m_renderer, m_texture, &m_weaponSource.at(i), &m_weaponTarget.at(i));
            }
        }

        //Rendering of the Evolution Stage
        Vector2i evolutionPosition;
        evolutionPosition.setX(m_weaponPosition.x() + (m_weaponName.length() * m_tileWidth) + 2 * m_tileWidth);
        evolutionPosition.setY(m_horziontalAlignemnt);
        displayNumber(std::stoi(m_evolutionStage) - 1, evolutionPosition, source, target);

        //Rendering of Health Display
        displayNumber(m_health, m_healthPosition, source, target);
    }

    void StatusBar::displayNumber(int number, Vector2i position, SDL_Rect source, SDL_Rect target) {
        vector<Vector2i> vec_source = renderNumber(number, m_numberOffset);
        for (int i = 0; i < vec_source.size(); i++) {
            source.x = vec_source[i].x();
            source.y = vec_source[i].y();

            target.x = position.x() + (i * m_tileWidth) + i;
            target.y = position.y();
            SDL_RenderCopy(m_renderer, m_texture, &source, &target);
        }
    }

    void StatusBar::setPosition(const Vector2i &positionStart, const Vector2i &positionEnd) {
        m_startPosition = positionStart;
        m_endPosition = positionEnd;
        //to get the vertical alignment straight, we need to substract our tileheight from the middle of our statusbar
        //and substract to offset to get it perfectly horizontally aligned
        m_horziontalAlignemnt = (m_startPosition.y() / 2) - ((m_tileHeight / 2) - m_offsetMiddle);
        setScorePosition(Vector2i(m_startPosition.x() + 10, m_horziontalAlignemnt));
        //TODO ~ Update Weapon Position, so its always in the middle.
        setWeaponPosition(Vector2i(m_endPosition.x() / 2, m_horziontalAlignemnt));
        setHealthPosition(Vector2i(m_endPosition.x() - 10 - 3 * m_tileWidth, m_horziontalAlignemnt));
    }

    void StatusBar::setScorePosition(const Vector2i &position) {
        m_scorePosition = position;
    }

    void StatusBar::setWeaponPosition(const Vector2i &position) {
        m_weaponPosition = position;
    }

    void StatusBar::setHealthPosition(const Vector2i &position) {
        m_healthPosition = position;
    }

    void StatusBar::setWeaponName(string weaponName) {
        m_weaponChanged = false;
        if (weaponName != m_weaponName) {
            m_weaponChanged = true;
            m_weaponName = weaponName;
        }
    }

    void StatusBar::setEvolutionStage(string evolutionStage) {
        m_evolutionStage = evolutionStage;
    }

    void StatusBar::setHealth(int health) {
        m_health = health;
    }

    StatusBar::~StatusBar() {
        // TODO Auto-generated destructor stub
    }

} /* namespace jumper */

