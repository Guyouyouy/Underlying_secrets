#include <stdio.h>
#include <stdlib.h>

// 定义回调函数的类型
typedef void (*Callback)(void* arg);

// 事件订阅者结构体，用于存储回调函数及其参数
typedef struct Subscriber {
    Callback callback;
    void* arg;
} Subscriber;

// 事件管理器，用于存储订阅者信息
typedef struct EventManager {
    Subscriber* subscribers;
    int count;
} EventManager;

// 初始化事件管理器
void initEventManager(EventManager* manager) {
    manager->subscribers = NULL;
    manager->count = 0;
}

// 注册回调函数
void registerCallback(EventManager* manager, Callback cb, void* arg) {
    manager->count++;
    manager->subscribers = (Subscriber*)realloc(manager->subscribers, manager->count * sizeof(Subscriber));
    manager->subscribers[manager->count - 1].callback = cb;
    manager->subscribers[manager->count - 1].arg = arg;
}

// 触发事件
void triggerEvent(EventManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        // 调用每个订阅者的回调函数
        manager->subscribers[i].callback(manager->subscribers[i].arg);
    }
}

// 清理资源
void cleanupEventManager(EventManager* manager) {
    free(manager->subscribers);
    manager->subscribers = NULL;
    manager->count = 0;
}

// 示例回调函数
void myCallback(void* arg) {
    printf("Callback called with argument: %s\n", (char*)arg);
}

int main() {
    EventManager manager;
    initEventManager(&manager);

    // 注册回调函数
    registerCallback(&manager, myCallback, "Hello, World!");
    registerCallback(&manager, myCallback, "This is a test.");

    // 触发事件，调用所有注册的回调函数
    triggerEvent(&manager);

    // 清理资源
    cleanupEventManager(&manager);

    return 0;
}