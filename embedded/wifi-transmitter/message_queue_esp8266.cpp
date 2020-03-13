#include "message_queue.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "message.h"
#include "debug.h"

class message_queue_impl {
  QueueHandle_t queue;
public:
  message_queue_impl() {
    queue = xQueueCreate(10, sizeof(message));
  }
  virtual ~message_queue_impl() {};
  void push(const message &m) {
    xQueueSend(queue, (void*) &m,(TickType_t) 0 );
  }
  message wait(bool *ok) const {
    *ok=false;
    message ret;
    /* Block for 500ms. */
    const TickType_t timeout = 500 / portTICK_PERIOD_MS;
    if(xQueueReceive(queue,&ret,timeout) == pdPASS ) {
      *ok=true;
      return ret;
    }
    return message(0);
  }
};

message_queue::message_queue():impl(new message_queue_impl) {
}

void message_queue::push(const message &m) {
  return impl->push(m);
}

message message_queue::wait(bool *ok) {
  return impl->wait(ok);
}
