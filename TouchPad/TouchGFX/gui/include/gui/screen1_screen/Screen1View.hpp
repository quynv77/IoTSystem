#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
// Thêm các include cần thiết
#include <touchgfx/widgets/canvas/Circle.hpp> // Chỉ cần include Circle
#include <touchgfx/hal/Types.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Các hàm để liên kết với button trong TouchGFX Designer
    virtual void leftClick();
    virtual void rightClick();
    virtual void mouseHandler();

protected:
    // Các hàm xử lý sự kiện của TouchGFX
    virtual void handleDragEvent(const touchgfx::DragEvent& evt);
    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);
    virtual void handleTickEvent();

private:
    int16_t lastX;
    int16_t lastY;

    // Chỉ cần widget Circle, không cần Painter
    touchgfx::Circle touchCircle;

    int circleVisibleCounter;
};

#endif // SCREEN1VIEW_HPP
