#include <pebble.h>
  
enum {
  KEY_TOGGLE_SOFTROOM = 0,
  KEY_TOGGLE_HARDROOM = 1,
  KEY_TOGGLE_KITCHEN  = 2,
  KEY_TOGGLE_CORRIDOR = 3
};
  
static Window* mainWindow;
static TextLayer* textLayer;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(textLayer, "Up pressed!");
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
}

static void mainWindowLoad(Window* window) {
  Layer* windowLayer = window_get_root_layer(window);
  GRect windowBounds = layer_get_bounds(windowLayer);

  // Create output TextLayer
  textLayer = text_layer_create(GRect(5, 0, windowBounds.size.w - 5, windowBounds.size.h));
  text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(textLayer, "HS KRK TEST");
  text_layer_set_overflow_mode(textLayer, GTextOverflowModeWordWrap);
  layer_add_child(windowLayer, text_layer_get_layer(textLayer));
}

static void mainWindowUnload(Window* window) {
  text_layer_destroy(textLayer);
}

static void init() {
  mainWindow = window_create();
  
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = mainWindowLoad,
    .unload = mainWindowUnload
  });
  
  window_set_click_config_provider(mainWindow, click_config_provider);
  window_stack_push(mainWindow, true);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  window_destroy(mainWindow);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
  return 0;
}
