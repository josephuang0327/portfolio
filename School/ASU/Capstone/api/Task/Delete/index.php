<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

if (!isset($_POST['task_ID'])) {
    die(ReturnError(3,"Incorrect Parameters"));
}

# vars go here
# active will always be set to true, given that the task has just been created
$task_ID = $_POST['task_ID'];
$Author_ID_FK = $GLOBALS['myID'];

#To test, Change to _GET
$stmt = $mysqli->prepare("DELETE FROM `Task` WHERE `Task_ID` = ? AND `Author_ID_FK` = ?");

if (false === $stmt) {
    // Since all the following operations need a valid/ready statement object
    // it doesn't make sense to go on
    die(ReturnError(2,"Unexpected Unknown Error"));
}

$bind = $stmt->bind_param("is", $task_ID, $Author_ID_FK);

if (false === $bind) {
    die(ReturnError(2,"Unexpected Unknown Error"));
}

$exec = $stmt->execute();

if (false === $exec) {
    die(ReturnError(2,"Unexpected Unknown Error"));
}

if ($mysqli->affected_rows > 0) {
    die(NoErr());
}
die(ReturnError(2,"Unexpected Unknown Error"));