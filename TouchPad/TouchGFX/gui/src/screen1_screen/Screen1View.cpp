#include <gui/screen1_screen/Screen1View.hpp>
#include "usbd_hid.h"
#include <touchgfx/Color.hpp>
#include "stm32f4xx_hal.h"

// Cấu trúc báo cáo HID cho chuột (đã sửa)
typedef struct {
    uint8_t button;
    int8_t  x;
    int8_t  y;
    int8_t  wheel;
} mouseHID_t;

extern USBD_HandleTypeDef hUsbDeviceHS;

mouseHID_t mouseReport = {0, 0, 0, 0};

Screen1View::Screen1View()
    : lastX(-1), lastY(-1), circleVisibleCounter(0)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    // --- Cấu hình hình tròn màu trắng đơn giản ---
    touchCircle.setPosition(0, 0, 50, 50); // Đặt kích thước cho widget
    touchCircle.setCenter(25, 25);         // Tâm tương đối với widget
    touchCircle.setRadius(25);
    touchCircle.setLineWidth(5);           // Vẽ hình tròn đặc
    touchCircle.setArc(0, 360);


    // Ban đầu ẩn đi
    touchCircle.setVisible(false);

    // Thêm vào màn hình
    add(touchCircle);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleDragEvent(const touchgfx::DragEvent& evt)
{
    Screen1ViewBase::handleDragEvent(evt);

    if (lastX == -1 || lastY == -1) {
        lastX = evt.getNewX();
        lastY = evt.getNewY();
        return;
    }

    int8_t deltaX = evt.getNewX() - lastX;
    int8_t deltaY = evt.getNewY() - lastY;

    lastX = evt.getNewX();
    lastY = evt.getNewY();

    mouseReport.button = 0;
    mouseReport.x = deltaX;
    mouseReport.y = deltaY;
    mouseReport.wheel = 0;

    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));
    HAL_Delay(1);
}

void Screen1View::handleClickEvent(const touchgfx::ClickEvent& evt)
{
    Screen1ViewBase::handleClickEvent(evt);

    if (evt.getType() == touchgfx::ClickEvent::PRESSED)
    {
        // Di chuyển hình tròn đến điểm chạm (đã sửa lỗi getRadius)
        touchCircle.moveTo(evt.getX() - (touchCircle.getWidth() / 2), evt.getY() - (touchCircle.getHeight() / 2));
        touchCircle.setVisible(true);
        touchCircle.invalidate();

        // Đặt thời gian hiển thị
        circleVisibleCounter = 10;
    }

    // Reset lại trạng thái kéo
    lastX = -1;
    lastY = -1;
    HAL_Delay(1);
}

void Screen1View::handleTickEvent()
{
    if (circleVisibleCounter > 0)
    {
        circleVisibleCounter--;
        if (circleVisibleCounter == 0)
        {
            touchCircle.setVisible(false);
            touchCircle.invalidate();
        }
    }
    HAL_Delay(1);
}

void Screen1View::leftClick()
{
    // Nhấn chuột trái
    mouseReport.button = 0x01;
    mouseReport.x = 0;
    mouseReport.y = 0;
    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));

    // Thả chuột trái
    mouseReport.button = 0x00;
    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));
    HAL_Delay(1);
}

void Screen1View::rightClick()
{
    // Nhấn chuột phải
    mouseReport.button = 0x02;
    mouseReport.x = 0;
    mouseReport.y = 0;
    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));

    // Thả chuột phải
    mouseReport.button = 0x00;
    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));
    HAL_Delay(1);
}

void Screen1View::mouseHandler()
{
    // Không dùng, để trống
}
