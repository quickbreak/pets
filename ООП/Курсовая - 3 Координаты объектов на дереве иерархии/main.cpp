#include "application.h"
#include <iostream>


int main() {
	application app(NULL);
	app.build_tree_objects();
	return app.exec_app();

}


/*
input:
rootela
/ object_1 3
/ object_2 2
/object_2 object_4 3
/object_2 object_5 4
/ object_3 3
/object_2 object_3 6
/object_1 object_7 5
/object_2/object_4 object_7 3
endtree
FIND object_2/object_4
SET /object_2
FIND //object_7
FIND object_4/object_7
FIND .
FIND .object_7
FIND object_4/object_7
MOVE .object_7
SET object_4/object_7
MOVE //object_1
MOVE /object_3
END


output:
Object tree
rootela
    object_1
        object_7
    object_2
        object_4
            object_7
        object_5
        object_3
    object_3
object_2/object_4     Object name: object_4
Object is set: object_2
//object_7     Object is not found
object_4/object_7     Object name: object_7
.     Object name: object_2
.object_7     Object name: object_7
object_4/object_7     Object name: object_7
.object_7     Redefining the head object failed
Object is set: object_7
//object_1     Dubbing the names of subordinate objects
New head object: object_3
Current object hierarchy tree
rootela
    object_1
        object_7
    object_2
        object_4
        object_5
        object_3
    object_3
        object_7


input:
root
/ object_1 3
/ object_2 2
endtree
DELETE object_1
DELETE object_1
END

output:
Object tree
root
    object_1
    object_2
The object /object_1 has been deleted
Current object hierarchy tree
root
    object_2


input:
root
/ object_1 2
/object_1 object_2 3
endtree
SET object_2
END

output:
Object tree
root
    object_1
        object_2
The object was not found at the specified coordinate: object_2
Current object hierarchy tree
root
    object_1
        object_2


input:
root
/ object_1 2
/ object_1 3
endtree
MOVE object_1
END

output:
/     Dubbing the names of subordinate objects
Object tree
root
    object_1
object_1     Redefining the head object failed
Current object hierarchy tree
root
    object_1


input:
root
/ object_1 2
object_4 object_2 3
/ object_3 5
endtree
END

output:
Object tree
root
    object_1
The head object object_4 is not found

*/