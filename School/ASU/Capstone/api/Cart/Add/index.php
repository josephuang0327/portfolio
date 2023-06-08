<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

if (!isset($_POST['Task_ID'])) {
    die(ReturnError(3,"Incorrect Parameters"));
}

$User_ID = $GLOBALS['myID'];
$Task_ID = $_POST['Task_ID'];
$succeed = false;
$stmt = $mysqli->prepare("INSERT INTO `Cart` (`UserID_FK`, `TaskID_FK`) VALUES (?, ?);");

$stmt->bind_param("si", $User_ID, $Task_ID);
$succeed = $stmt->execute();

if ($succeed) {
    die(NoErr());
}
die(ReturnError(2,"Unexpected Unknown Error"));
