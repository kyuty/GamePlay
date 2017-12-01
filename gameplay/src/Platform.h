#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Vector2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Touch.h"
#include "Gesture.h"
#include "Gamepad.h"
#include "FileSystem.h"

namespace gameplay
{

class Game;

/**
 * Defines a platform abstraction.
 *
 * This class has only a few public methods for creating a platform
 *
 * 定义平台抽象类
 *
 * 为创建平台，提供少量公共方法
 */
class Platform
{
public:

    friend class Game;
    friend class Gamepad;
    friend class ScreenDisplayer;
    friend class FileSystem;

    /**
     * Destructor.
     */
    ~Platform();

    /**
     * Creates a platform for the specified game which it will interact with.
     *
     * 创建 与特殊的Game类相互作用的 platform类
     *
     * @param game The game to create a platform for.
     *
     * @return The created platform interface.
     * @script{ignore}
     */
    static Platform* create(Game* game);

    /**
     * Begins processing the platform messages.
     *
     * This method handles all OS window messages and drives the game loop.
     * It normally does not return until the application is closed.
     *
     * If a attachToWindow is passed to Platform::create the message pump will instead attach
     * to or allow the attachToWindow to drive the game loop on the platform.
     *
     * 开始处理平台信息
     *
     * 该方法处理所有系统窗口消息，并且驱动game循环
     * 一般情况下它是不返回的，除非应用程序关闭
     *
     * 如果attachToWindow被传递给Platform::create，消息循环机将会附加或允许attachToWindow方法去驱动
     * 游戏循环
     *
     * pump 泵，抽水机，程序不断循环
     *
     * @return The platform message pump return code.
     */
    int enterMessagePump();

    /**
     * Swaps the frame buffer on the device.
     */
    static void swapBuffers();

private:

    /**
     * This method informs the platform that the game is shutting down
     * and anything platform specific should be shutdown as well or halted
     * This function is called automatically when the game shutdown function is called
     *
     * 该方法通知平台，游戏正在关闭
     * 以及任何特定平台应该关闭或停止
     *
     * 当游戏调用关闭方法时，这个方法会自动被调用
     *
     * as well or : 或者
     */
    static void signalShutdown();

    /**
     * Indicates whether a programmatic exit is allowed on this platform.
     * Some platforms (eg. iOS) do not allow apps to exit programmatically.
     *
     * 表示在此平台是否允许程序退出
     * 一些平台，如iOS，不允许应用程序以编程的方式退出
     *
     * @return whether a programmatic exit is allowed on this platform.
     */
    static bool canExit();

    /**
     * Gets the display width.
     *
     * @return The display width.
     */
    static unsigned int getDisplayWidth();

    /**
     * Gets the display height.
     *
     * @return The display height.
     */
    static unsigned int getDisplayHeight();

    /**
     * Gets the absolute platform time starting from when the message pump was started.
     *
     * 从消息循环开始计，获取平台绝对时间
     *
     * @return The absolute platform time. (in milliseconds)
     */
    static double getAbsoluteTime();

    /**
     * Sets the absolute platform time since the start of the message pump.
     *
     * 虽然消息循环已经开始，但依旧可以设置平台的绝对时间
     *
     * @param time The time to set (in milliseconds).
     */
    static void setAbsoluteTime(double time);

    /**
     * Gets whether vertical sync is enabled for the game display.
     *
     * @return true if vsync is enabled; false if not.
     */
    static bool isVsync();

    /**
     * Sets whether vertical sync is enable for the game display.
     *
     * @param enable true if vsync is enabled; false if not.
     */
    static void setVsync(bool enable);

    /**
     * Sleeps synchronously for the given amount of time (in milliseconds).
     *
     * ms毫秒休眠(同步，非异步)
     *
     * @param ms How long to sleep (in milliseconds).
     */
    static void sleep(long ms);

    /**
     * Set if multi-sampling is enabled on the platform.
     *
     * multi-sampling : 多点采样
     *
     * @param enabled true sets multi-sampling to be enabled, false to be disabled.
     */
    static void setMultiSampling(bool enabled);

   /**
    * Is multi-sampling mode enabled.
    *
    * multi-sampling : 多点采样
    *
    */
    static bool isMultiSampling();

    /**
     * Set if multi-touch is enabled on the platform.
     *
     * Note that this method does nothing on platforms that do not
     * support multi-touch.
     */
    static void setMultiTouch(bool enabled);

   /**
    * Is multi-touch mode enabled.
    */
    static bool isMultiTouch();

    /**
     * Whether the platform has mouse support.
     *
     * 是否有鼠标
     */
    static bool hasMouse();

    /**
     * Enables or disabled mouse capture.
     *
     * 开启或关闭鼠标捕捉
     *
     * When mouse capture is enabled, the platform cursor is hidden
     * and mouse event points are delivered as position deltas instead
     * of absolute positions.
     *
     * This is useful for games that wish to provide uninhibited mouse
     * movement, such as when implementing free/mouse look in an FPS
     * game.
     *
     * 当开启鼠标捕捉，平台光标被隐藏。
     * 鼠标事件点将作为位置增量而不是绝对位置来传递。
     *
     * 这对希望提供不受限制的鼠标游戏很有用，
     * 比如说在FPS游戏通过鼠标实现自由视角
     *
     * Disabling mouse capture moves the mouse back to the center of the
     * screen and shows the platform cursor.
     *
     * 关闭鼠标捕捉，平台光标显示，将鼠标位置移动到屏幕中心
     *
     * Note that this method does nothing on platforms that do not
     * support a mouse.
     *
     * @param captured True to enable mouse capture, false to disable it.
     */
    static void setMouseCaptured(bool captured);

    /**
     * Determines if mouse capture is currently enabled.
     */
    static bool isMouseCaptured();

    /**
     * Sets the visibility of the platform cursor.
     *
     * 设置是否显示鼠标光标
     *
     * On platforms that support a visible cursor, this method
     * toggles the visibility of the cursor.
     *
     * @param visible true to show the platform cursor, false to hide it.
     */
    static void setCursorVisible(bool visible);

    /**
     * Determines whether the platform cursor is currently visible.
     *
     * @return true if the platform cursor is visible, false otherwise.
     */
    static bool isCursorVisible();

    /**
     * Whether the platform has accelerometer support.
     *
     * 是否有加速计
     */
    static bool hasAccelerometer();

    /**
     * Gets the platform accelerometer values for use as an indication of device
     * orientation. Despite its name, implementations are at liberty to combine
     * accelerometer data with data from other sensors as well, such as the gyros.
     * This method is best used to obtain an indication of device orientation; it
     * does not necessarily distinguish between acceleration and rotation rate.
     *
     * @param pitch The accelerometer pitch. Zero if hasAccelerometer() returns false.
     * @param roll The accelerometer roll. Zero if hasAccelerometer() returns false.
     */
    static void getAccelerometerValues(float* pitch, float* roll);

    /**
     * Gets sensor values (raw), if equipped, allowing a distinction between device acceleration
     * and rotation rate. Returns zeros on platforms with no corresponding support. See also
     * hasAccelerometer() and getAccelerometerValues().
     *
     * @param accelX The x-coordinate of the raw accelerometer data.
     * @param accelY The y-coordinate of the raw accelerometer data.
     * @param accelZ The z-coordinate of the raw accelerometer data.
     * @param gyroX The x-coordinate of the raw gyroscope data.
     * @param gyroY The y-coordinate of the raw gyroscope data.
     * @param gyroZ The z-coordinate of the raw gyroscope data.
     */
    static void getSensorValues(float* accelX, float* accelY, float* accelZ, float* gyroX, float* gyroY, float* gyroZ);

    /**
     * Gets the command line arguments.
     *
     * 获取命令行的参数
     * 在Linux和Windows平台生效，Android不生效
     *
     * @param argc The number of command line arguments.
     * @param argv The array of command line arguments.
     */
    static void getArguments(int* argc, char*** argv);

    /**
     * Shows or hides the virtual keyboard (if supported).
     *
     * 是否显示垂直键盘
     *
     * @param display true when virtual keyboard needs to be displayed and false otherwise.
     */
    static void displayKeyboard(bool display);

    /**
     * Tests if the specified gesture is supported on the platform.
     *
     * 测试这个特殊的手势是否在当前平台支持
     *
     * @return true if it is supported; false if not supported.
     */
    static bool isGestureSupported(Gesture::GestureEvent evt);

    /**
     * Registers the platform for gesture recognition for the specified gesture event.
     *
     * @param evt The gesture event to register to start recognizing events for.
     */
    static void registerGesture(Gesture::GestureEvent evt);

    /**
     * Registers the platform for gesture recognition for the specified gesture event.
     *
     * @param evt The gesture event to register to start recognizing events for.
     */
    static void unregisterGesture(Gesture::GestureEvent evt);

    /**
     * Tests if the specified gesture is registered for gesture recognition for the specified gesture event
     *
     * @param evt The gesture event to register to start recognizing events for.
     */
    static bool isGestureRegistered(Gesture::GestureEvent evt);

    /**
     * Opens an URL in an external browser, if available.
     *
     * @param url URL to be opened.
     *
     * @return True if URL was opened successfully, false otherwise.
     */
    static bool launchURL(const char* url);

    /**
     * Constructor.
     */
    Platform(Game* game);

    /**
     * Constructor.
     */
    Platform(const Platform& copy);

public:

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void touchEventInternal(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex, bool actuallyMouse = false);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void keyEventInternal(Keyboard::KeyEvent evt, int key);

   /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static bool mouseEventInternal(Mouse::MouseEvent evt, int x, int y, int wheelDelta);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gestureSwipeEventInternal(int x, int y, int direction);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gesturePinchEventInternal(int x, int y, float scale);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gestureTapEventInternal(int x, int y);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
	static void gestureLongTapEventInternal(int x, int y, float duration);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
	static void gestureDragEventInternal(int x, int y);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
	static void gestureDropEventInternal(int x, int y);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void resizeEventInternal(unsigned int width, unsigned int height);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadEventConnectedInternal(GamepadHandle handle, unsigned int buttonCount, unsigned int joystickCount, unsigned int triggerCount, const char* name);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadEventDisconnectedInternal(GamepadHandle handle);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadButtonPressedEventInternal(GamepadHandle handle, Gamepad::ButtonMapping mapping);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadButtonReleasedEventInternal(GamepadHandle handle, Gamepad::ButtonMapping button);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadTriggerChangedEventInternal(GamepadHandle handle, unsigned int index, float value);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void gamepadJoystickChangedEventInternal(GamepadHandle handle, unsigned int index, float x, float y);

    /**
     * Internal method used to poll the platform for the updated Gamepad
     * states such as buttons, joytick and trigger values.
     *
     * Some platforms require to poll the gamepad system to get deltas. 
     *
     * @param gamepad The gamepad to be returned with the latest polled values populated.
     * @script{ignore}
     */
    static void pollGamepadState(Gamepad* gamepad);

    /**
     * Displays an open or save dialog using the native platform dialog system.
     *
     * @param mode The mode of the dialog. (Ex. OPEN or SAVE)
     * @param title The title of the dialog. (Ex. Select File or Save File)
     * @param filterDescription The file filter description. (Ex. Image Files)
     * @param filterExtensions The semi-colon delimited list of filtered file extensions. (Ex. png;jpg;bmp)
     * @param initialDirectory The initial directory to open or save files from. (Ex. "res") If NULL this will use the executable directory.
     * @return The file that is opened or saved, or an empty string if canceled.
     *
     * @script{ignore}
     */
    static std::string displayFileDialog(size_t mode, const char* title, const char* filterDescription, const char* filterExtensions, const char* initialDirectory);

    /**
     * Internal method used only from static code in various platform implementation.
     *
     * @script{ignore}
     */
    static void shutdownInternal();

private:

    Game* _game;                // The game this platform is interfacing with.
};

}

#include "Game.h"

#endif
