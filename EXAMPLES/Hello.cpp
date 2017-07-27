#include "Pokitto.h"
#include <new>          // std::nothrow SIMULATOR!!!


Pokitto::Core game;

/** Select the test code */
#define TEST_MAIN 1

/** Test: Hello World */
#if TEST_MAIN == 0

int main () {
    game.begin();
    // Next 4 lines are just to show the C64 font, you can comment them out by adding // in the start of the line
    game.display.setFont(fntC64gfx);
    game.display.palette[0] = game.display.RGBto565(0x0, 0x0, 0x0); //default background is palette[0]
    game.display.palette[1] = game.display.RGBto565(0x00, 0xff, 0x00); //default foreground is palette[1]
    game.display.palette[2] = game.display.RGBto565(0xff, 0x00, 0x00); // red
    game.display.palette[3] = game.display.RGBto565(0xff, 0xff, 0xff); // white
    //game.display.palette[4] = game.display.RGBto565(0xff, 0xff, 0xff);  // white
    game.display.charSpacingAdjust = 0; //needed for the non-proportional C64 font (normal value=1)

    Pokitto::Window* win1 = new(std::nothrow) Pokitto::Window();
    win1->setTitle("POKITTO");
    Pokitto::WidgetBase* win2 = new(std::nothrow) Pokitto::WidgetBase(Pokitto::WidgetBase::hasBorders);
    //win->setRect(0, 0, game.display.getWidth(), game.display.getHeight());
    //win->setRect(0, 0, 64, 64);

    Pokitto::ListBox* listbox = new(std::nothrow) Pokitto::ListBox(Pokitto::WidgetBase::hasBorders);
    listbox->init(0, 0, 10, 5, 20, 0);
    listbox->addItem("FIRST 1234567890");
    listbox->addItem("SECOND");
    listbox->addItem("THIRD");
    listbox->addItem("4TH");
    listbox->addItem("5TH");
    listbox->addItem("6TH");
    listbox->addItem("7TH");
    listbox->addItem("8TH");

	bool mustDraw = true;
	int16_t sx=128, sy=128;
    while (game.isRunning()) {
        if (game.update()) {
            //game.display.print("Hello World!");
            //game.display.print("**** COMMODORE 64 LIVES ****\n\n");
            //game.display.println(" 32K RAM POKITTO SYSTEM \n");
            //game.display.println("READY.");

            // Draw
            if (mustDraw) {

                game.display.color = 1;
                //win1->setRect(0, 0, sx, sy);
                //win1->draw();
                //win2->setRect(40, 40, sx, sy);
                //win2->draw();

                listbox->update();
                listbox->draw();

                game.display.color = 2;
                game.display.drawRect(0, 0, sx, sy);

                //game.display.println(0,130,"aabacadaeafagahaiajakalamanaoapaqarasatauavaw");
                //game.display.println("abcdefghijklmnopqrstuvw");
                //game.display.println("ABCDEFGHIJKLMNOPQRSTUVW");
                //game.display.println("a b c d e f g h i j k l m n o p q r s t u v w");

                 mustDraw = false;
           }
#if 0
            // Read key
            if(game.buttons.repeat(BTN_RIGHT,0)) {
                mustDraw = true;
                sx+=2;
                //if(sx > 0  )
                //    sx = 0;
            }
            if(game.buttons.repeat(BTN_LEFT,0)) {
                mustDraw = true;
                sx-=2;
                //if (sx < game.display.width-imageW)
                //    sx = game.display.width-imageW;
            }
            if(game.buttons.repeat(BTN_UP,0)) {
                mustDraw = true;
                sy-=2;
                //if (sy < game.display.height-imageH)
                //    sy = game.display.height-imageH;
            }
            if(game.buttons.repeat(BTN_DOWN,0)) {
                mustDraw = true;
                sy+=2;
                //if(sy > 0  )
                //    sy = 0;
            }
#endif
        }
    }

    delete(win2);
    delete(win1);

    return 1;
}

/** Test: Custom control */
#elif TEST_MAIN == 1

/** CUSTOM WIDGET */
class MyCustomControl : public Pokitto::Window {

public:
    MyCustomControl() {m_listbox = NULL;}
    ~MyCustomControl(){delete m_listbox;}

    init() {
        setTitle("POKITTO");
        setRect(0, 0, game.display.getWidth()-1, game.display.getHeight());

        int16_t vx, vy, vw, vh;
        getViewRect(vx, vy, vw, vh);
        m_listbox = new(std::nothrow) Pokitto::ListBox(Pokitto::WidgetBase::hasBorders);
        m_listbox->init(vx, vy, vw/Pokitto::fontW/2, vh/Pokitto::fontH - 2, 100, 0);
        char itemName[256];
        for (int16_t i=0; i<50; i++) {
            sprintf(itemName, "%d\. ITEM 1234567890", i);
            m_listbox->addItem(itemName);
        }
   }

    // Inherited
    void draw() {
        Window::draw();
        m_listbox->update(); // To react scrolling
        m_listbox->draw();
    }

public:
    Pokitto::ListBox* m_listbox;
};

/** MAIN */
int main () {
    game.begin();

    game.display.setFont(fntC64gfx);
    game.display.palette[0] = game.display.RGBto565(0x0, 0x0, 0x0); //default background is palette[0]
    game.display.palette[1] = game.display.RGBto565(0x00, 0xff, 0x00); //default foreground is palette[1]
    game.display.palette[2] = game.display.RGBto565(0xff, 0x00, 0x00); // red
    game.display.palette[3] = game.display.RGBto565(0xff, 0xff, 0xff); // white
    game.display.charSpacingAdjust = 0; //needed for the non-proportional C64 font (normal value=1)

    MyCustomControl* control = new(std::nothrow) MyCustomControl();
    control->init();

	bool mustDraw = true;
    while (game.isRunning()) {
        if (game.update()) {

            // Draw
            if (mustDraw) {
                game.display.color = 1;
                control->draw();
                //mustDraw = false;
            }
        }
    }

    delete(control);
    return 1;
}
#endif


