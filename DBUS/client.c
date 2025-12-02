#include <dbus/dbus.h>
#include <stdio.h>

int main() {
    DBusConnection* conn;
    DBusError err;
    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn) {
        fprintf(stderr, "DBus 연결 실패: %s\n", err.message);
        return 1;
    }

    dbus_bus_add_match(conn, "type='signal',interface='com.example.Notify'", &err);
    dbus_connection_flush(conn);

    printf("클라이언트 시작, 메시지 대기 중...\n");

    while (1) {
        dbus_connection_read_write(conn, 0);
        DBusMessage* msg = dbus_connection_pop_message(conn);

        if (msg) {
            if (dbus_message_is_signal(msg, "com.example.Notify", "Message")) {
                const char* text;
                dbus_message_get_args(msg, &err, DBUS_TYPE_STRING, &text, DBUS_TYPE_INVALID);
                printf("받은 메시지: %s\n", text);
            }
            dbus_message_unref(msg);
        }
    }

    return 0;
}
