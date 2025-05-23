# COMP3004 Final Project: Tandem Insulin Pump

This project models the interaction flow of a t:slim X2 insulin pump with Control-IQ technology and a CGM sensor, using PlantUML sequence diagrams. It covers real-world scenarios like meal-time bolus delivery, insulin on board (IOB) adjustments, extended bolus options, and glucose trend monitoring. The diagram is based on clinical logic using insulin-to-carb ratios, correction factors, and safety checks for effective diabetes management.

**Team members:**
Rieley
Kate
Jackson
Yunes
Kevin

**Responsibilities:**
Rieley:

- InsulinGauge
- InsulinReservoir
- GlucoseMonitor
- InsulinStartScreen
- InsulinStopScreen

Jackson:

- ProfileManageScreen
- ProfileEditorDialog
- UserProfile
- PumpScreen
- SimConfigWindow
- PumpSimulation

Kate:

- GlucoseMonitor
- Delivery history
- History screen UI
- Insulin, CGM and error data types 
- Error dialog UI
- Error handler

Kevin:

- HomeScreen
- DataGraph
- SettingsScreen
- SystemsSettings

Yunes:

- BatteryIndicator
- BatteryManager
- BolusScreen
- BolusCalculator
- DeliverySettings

**File Structure:**

AlarmPopup.h	Popup alert screen for alarms like low insulin, low battery, or pump failure.

BasePumpScreen.h	Base class for all pump screens, providing consistent UI elements like navigation bars.

BatteryIndicator.h	Displays real-time battery level inside the pump UI.

BatteryManager.h	Monitors battery status and manages charging behavior.

BolusCalculator.h	Calculates insulin bolus doses based on carb intake, blood glucose, and insulin sensitivity.

BolusScreen.h	Screen for users to input carbs, BG, and request boluses (immediate or extended).

ConfigDialog.h	Dialog for configuring glucose event simulations during testing.

DataGraph.h	Dynamic chart that displays blood glucose trends over time using CGM data.

DeliveryError.h	Represents an error type (low glucose, low insulin, pump failure, etc.).

DeliveryEvent.h	Represents a single insulin delivery event (timestamp + dose).

DeliveryHistory.h	Stores all past boluses, glucose readings, and delivery-related errors.

DeliverySettings.h	Stores insulin delivery settings like basal rates or target BG.

ErrorDialog.h	Displays error messages visually to the user.

ErrorHandler.h	Handles errors by logging them and showing dialogs.

ExerciseScreen.h	UI for entering exercise events affecting glucose levels.

GlucoseMonitor.h	Simulates real-time glucose behavior from meals, insulin, and exercise.

HistoryScreen.h	Displays history of CGM readings, boluses, and error events.

HomeScreen.h	Main dashboard screen: shows insulin level, access to graphs and options.

InsulinGauge.h	Graphical gauge displaying insulin reservoir levels.

InsulinPump.h	Core class representing the entire pump system logic and coordination.

InsulinReservoir.h	Manages insulin storage level and delivery into the system.

InsulinStartScreen.h	Screen to start insulin delivery manually.

InsulinStopScreen.h	Screen to stop insulin delivery manually and set reminders.

MealScreen.h	UI to log new meals into the glucose system.

OptionsScreen.h	Screen for user settings like history, profiles, and emergency insulin stop/start.

ProfileActionsScreen.h	Actions related to profiles (edit, activate, duplicate, delete).

ProfileData.h	Stores user-specific profile data (carb ratios, correction factors, etc.).

ProfileEditor.h	UI for editing the details of an insulin delivery profile.

ProfileListScreen.h	List of available user profiles (exercise, meal, sleep modes).

PumpSimulation.h	Provides timing simulation for glucose measurement events.

PumpWindow.h	Main application window managing all screen transitions and state.

TimedSetting.h	Represents a timed setting (e.g., different basal rates throughout the day).

TimedSettingEditor.h	UI screen for editing time-based insulin settings.

UserSettingsManager.h	Manages persistent user settings like PIN, brightness, and alert tones.

main.cpp	Entry point of the application: sets up and runs the simulation.
