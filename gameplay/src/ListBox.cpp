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
        // Get all ListItems objects
        Properties* listItemSpace = properties->getNextNamespace();
        while (listItemSpace != NULL)
        {
            const char* name = listItemSpace->getNamespace();
            if (strcmp(name, "listItem") == 0)
            {
                std::cout << "list item: " << name << std::endl;
                const char* text = listItemSpace->getString("text");
                float height = listItemSpace->getFloat("height");
                ListItem *item = new ListItem(text, height);
                _items.push_back(item);
            }
            else
            {
                std::cout << "ListBox expected 'listItem' as a child but '" << name << "' was found" << std::endl;
            }
            listItemSpace = properties->getNextNamespace();
        }
    }
}

void ListBox::changeSelectedItem(float x, float y)
{
    for (int i = 0; i < _items.size(); ++i) {
        ListItem *item = _items[i];
        bool itemContainsPosition = false;
        // TODO: Find if item contains x and y coordinates
        if (itemContainsPosition) {
            changeSelectedItem(i);
            return;
        }
    }
}

void ListBox::changeSelectedItem(int index)
{
    // TODO:
    // Do Validation: 0 <= index < _item.size()
    // Really change selected index
    // Change other variables for drawing
    // Broadcast SELECTED_ITEM_INDEX_CHANGED event
}
    
bool ListBox::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    if (getState() == ACTIVE) {
        switch (evt)
        {
            case Touch::TOUCH_PRESS:
                changeSelectedItem(x, y);
                break;
            case Touch::TOUCH_MOVE:
                changeSelectedItem(x, y);
                break;
            default:
                break;
        }
    }

    return Control::touchEvent(evt, x, y, contactIndex);
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
    // TODO: Do better keyboard handling. For example on the PC there is a *transitory* state
    // which is changed with the arrows keys. The space key makes the transitory item to be selected.
    // Further more Ctrl (or Command on OSX) allows multi selection
    switch (evt)
    {
        case Keyboard::KEY_PRESS:
        {
            switch (key)
            {
                case Keyboard::KEY_UP_ARROW:
                {
                    changeSelectedItem(_selectedIndex-1);
                    break;
                }
                case Keyboard::KEY_DOWN_ARROW:
                {
                    changeSelectedItem(_selectedIndex+1);
                    break;
                }
            }
        }
    }
    return Control::keyEvent(evt, key);
}

void ListBox::controlEvent(Control::Listener::EventType evt)
{
    //TODO: Do we need to do something here?
}

void ListBox::updateState(Control::State state)
{
    Control::updateState(state);
    _font = getFont(state);
    std::cout << "State " << state << " font: " << _font << std::endl;
}

unsigned int ListBox::drawImages(Form* form, const Rectangle& clip)
{
    // TODO: draw borders, dividers and highlighted item background
    return 0;
}

unsigned int ListBox::drawText(Form* form, const Rectangle& clip)
{
    // Draw the text.
    int drawCalls = 0;
    Rectangle bounds = _listBounds;
    for (std::vector<ListItem*>::const_iterator i = _items.begin(); i != _items.end(); ++i) {
        std::string *text = (*i)->text();
        float height = (*i)->height();
        if (text->size() > 0 && _font)
        {
            Control::State state = getState();
            unsigned int fontSize = getFontSize(state);
            if (height <= 0) {
                height = fontSize + 2; // add 2 because top margin and bottom margin
            }
            bounds.height = height;

            SpriteBatch* batch = _font->getSpriteBatch(fontSize);
            startBatch(form, batch);
            _font->drawText(text->c_str(), bounds, _textColor, fontSize, getTextAlignment(state), true, getTextRightToLeft(state), &_viewportClipBounds);
            finishBatch(form, batch);

            bounds.y += height;
            ++drawCalls;
        }
    }

    return drawCalls;
}

void ListBox::updateAbsoluteBounds(const Vector2& offset)
{
    Control::updateAbsoluteBounds(offset);
    _listBounds.set((int)_viewportBounds.x, (int)_viewportBounds.y, _viewportBounds.width, _viewportBounds.height);
}

void ListBox::update(float elapsedTime)
{
    Control::update(elapsedTime);

    // Update text opacity each frame since opacity is updated in Control::update.
    _textColor = getTextColor(getState());
    _textColor.w *= _opacity;
}



}