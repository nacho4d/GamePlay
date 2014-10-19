#include "ListBox.h"
#include "Game.h"

namespace gameplay
{

ListBox::ListBox()
{
}

ListBox::~ListBox()
{
}

ListBox* ListBox::create(const char* id, Theme::Style* style)
{
    ListBox* ListBox = new gameplay::ListBox();
    ListBox->_id = id ? id : "";
    ListBox->initialize("ListBox", style, NULL);
    return ListBox;
}

Control* ListBox::create(Theme::Style* style, Properties* properties)
{
    ListBox* ListBox = new gameplay::ListBox();
    ListBox->initialize("ListBox", style, properties);
    return ListBox;
}

void ListBox::addListener(Control::Listener* listener, int eventFlags)
{
    if ((eventFlags & Control::Listener::VALUE_CHANGED) == Control::Listener::VALUE_CHANGED)
    {
        GP_ERROR("VALUE_CHANGED event is not applicable to this control.");
    }
    Control::addListener(listener, eventFlags);
}

void ListBox::initialize(const char* typeName, Theme::Style* style, Properties* properties)
{
    Control::initialize(typeName, style, properties);
    if (properties)
    {
        //_inputMode = getInputMode(properties->getString("inputMode"));
    }
}
    
bool ListBox::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    return false;
}

/**
 * Keyboard callback on key events.
 *
 * @param evt The key event that occurred.
 * @param key If evt is KEY_PRESS or KEY_RELEASE then key is the key code from Keyboard::Key.
 *            If evt is KEY_CHAR then key is the unicode value of the character.
 *
 * @see Keyboard::KeyEvent
 * @see Keyboard::Key
 */
bool ListBox::keyEvent(Keyboard::KeyEvent evt, int key)
{
    return false;
}

/**
 * @see Control#controlEvent
 */
void ListBox::controlEvent(Control::Listener::EventType evt)
{
    
}

/**
 * @see Control::updateState
 */
void ListBox::updateState(Control::State state)
{
    
}

/**
 * @see Control::drawImages
 */
unsigned int ListBox::drawImages(Form* form, const Rectangle& clip)
{
    return 0;
}

/**
 * @see Control::drawText
 */
unsigned int ListBox::drawText(Form* form, const Rectangle& clip)
{
    return 0;
}

//    ListBox::ListBox(const ListBox& copy) {}


}