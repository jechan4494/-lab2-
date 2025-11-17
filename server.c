#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    DBusConnection* conn;
    DBusError err;
    dbus_error_init(&err);

    // 세션 버스 연결
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn) {
        fprintf(stderr, "DBus 연결 실패: %s\n", err.message);
        return 1;
    }

    // 메시지 생성
    DBusMessage* msg;
    msg = dbus_message_new_signal(
        "/com/example/Notify",     // object path
        "com.example.Notify",      // interface
        "Message"                  // signal name
    );

    if (!msg) {
        fprintf(stderr, "메시지 생성 실패\n");
        return 1;
    }

    const char* text = " test DBus 알림입니다.";
    dbus_message_append_args(msg, DBUS_TYPE_STRING, &text, DBUS_TYPE_INVALID);

    // 메시지 보내기
    if (!dbus_connection_send(conn, msg, NULL)) {
        fprintf(stderr, "메시지 전송 실패\n");
        return 1;
    }

    dbus_connection_flush(conn);
    printf("메시지 전송 완료\n");

    dbus_message_unref(msg);
    return 0;
}
