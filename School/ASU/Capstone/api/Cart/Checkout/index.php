<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

$User_ID = $GLOBALS['myID'];

$stmt = $mysqli->prepare("INSERT INTO `Receipts` (`UserID_FK`, `TaskID_FK`, `Cost`)(SELECT `UserID_FK`, `TaskID_FK`, cost FROM ky_capstone.Cart JOIN Task On `Task_ID` = Cart.TaskID_FK WHERE `UserID_FK` = ?);");

$stmt->bind_param("i", $User_ID);
$succeed = $stmt->execute();

#If it doesn't add anything to the receipt, we want to exit
if ($mysqli->affected_rows === 0 || !$succeed) {
    die(ReturnError(2,"Unexpected Unknown Error"));
}

$stmt = $mysqli->prepare("DELETE FROM `Cart` WHERE `UserID_FK` = ? ");

if (false === $stmt) {
    die(ReturnError(2,"Unexpected Unknown Error"));
}
$bind = $stmt->bind_param("i", $User_ID);

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
?>
