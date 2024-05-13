#include "application.h"
#include <iostream>


int main() {
	application app(NULL);
	app.build_tree_objects();
	return app.exec_app();

}

/*
input:

appls_root
/ object_s1 3
/ object_s2 2
/object_s2 object_s4 4
/ object_s13 5
/object_s2 object_s6 6
/object_s1 object_s7 2
endtree
/object_s2/object_s4 /object_s2/object_s6
/object_s2 /object_s1/object_s7
/ /object_s2/object_s4
/object_s2/object_s4 /
end_of_connections
EMIT /object_s2/object_s4 Send message 1
EMIT /object_s2/object_s4 Send message 2
EMIT /object_s2/object_s4 Send message 3
EMIT /object_s1 Send message 4
END

--output:
Object tree
appls_root
    object_s1
        object_s7
    object_s2
        object_s4
        object_s6
    object_s13
Signal from /object_s2/object_s4
Signal to /object_s2/object_s6 Text:  Send message 1 (class: 4)
Signal to / Text:  Send message 1 (class: 4)
Signal from /object_s2/object_s4
Signal to /object_s2/object_s6 Text:  Send message 2 (class: 4)
Signal to / Text:  Send message 2 (class: 4)
Signal from /object_s2/object_s4
Signal to /object_s2/object_s6 Text:  Send message 3 (class: 4)
Signal to / Text:  Send message 3 (class: 4)
Signal from /object_s1

input:
root
/ object_1 3
/ object_2 2
endtree
/ /object_1
/ /object_2
end_of_connections
EMIT / message 1
DELETE_CONNECT / /object_1
EMIT / message 2
END


--output:
Object tree
root
    object_1
    object_2
Signal from /
Signal to /object_1 Text: message 1 (class: 1)
Signal to /object_2 Text: message 1 (class: 1)
Signal from /
Signal to /object_2 Text: message 2 (class: 1)
*/