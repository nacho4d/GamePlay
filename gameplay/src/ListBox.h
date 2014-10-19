#ifndef LISTBOX_H
#define LISTBOX_H

#include <string>

#include "Control.h"

namespace gameplay
{
/**
 * Defines a ListBox control
 *
 * Listeners can listen for a SELECTED_INDEX_CHANGED event, and then query the list box
 * for the selected object
 *
 * @see http://blackberry.github.io/GamePlay/docs/file-formats.html#wiki-UI_Forms
 */
//class Container;
//class Form;
class ListBox : public Control {

//    friend class Container;
    friend class ControlFactory;

public:

    /**
     * Creates a new ListBox.
     *
     * @param id The listbox ID.
     * @param style The listbox style (optional).
     *
     * @return The new listbox.
     * @script{create}
     */
    static ListBox* create(const char* id, Theme::Style* style = NULL);

    virtual void addListener(Control::Listener* listener, int eventFlags);

protected:

    /**
     * Constructor.
     */
    ListBox();

    /**
     * Destructor.
     */
    ~ListBox();

    /**
     * Create a list box with a given style and properties.
     *
     * @param style The style to apply to this text box.
     * @param properties A properties object containing a definition of the text box (optional).
     *
     * @return The new text box.
     */
    static Control* create(Theme::Style* style, Properties* properties = NULL);

    /**
     * @see Control::initialize
     */
    void initialize(const char* typeName, Theme::Style* style, Properties* properties);

    /**
     * Touch callback on touch events.  Controls return true if they consume the touch event.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @return Whether the touch event was consumed by the control.
     *
     * @see Touch::TouchEvent
     */
    bool touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

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
    bool keyEvent(Keyboard::KeyEvent evt, int key);

    /**
     * @see Control#controlEvent
     */
    void controlEvent(Control::Listener::EventType evt);

    /**
     * @see Control::updateState
     */
    void updateState(State state);

    /**
     * @see Control::drawImages
     */
    unsigned int drawImages(Form* form, const Rectangle& clip);

    /**
     * @see Control::drawText
     */
    unsigned int drawText(Form* form, const Rectangle& clip);

private:

    /**
     * Constructor.
     */
    ListBox(const ListBox& copy);
};

}

#endif
