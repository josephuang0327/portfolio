<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

if (!isset($_GET['TaskID'])) {
    die(ReturnError(3,"Incorrect Parameters"));
}

#vars
$TaskID  = $_GET['TaskID'];

$stmt = $mysqli->prepare("SELECT * From Task WHERE `Task_ID` = ?");

$stmt->bind_param("i", $TaskID);

$succeed = $stmt->execute();
$result = $stmt->get_result();

$resultArray = $result->fetch_all(MYSQLI_ASSOC);
die(AppendNoErr($resultArray));
