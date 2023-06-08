<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

if (!isset($_POST['Name']) || !isset($_POST['UserType']) || !isset($_POST['BirthDate']) || !isset($_POST['City']) || !isset($_POST['PhoneNumber']) || !isset($_POST['Address']) || !isset($_POST['State']) || !isset($_POST['Zipcode'])) {
    die(ReturnError(3,"Incorrect Parameters"));
}

#vars
$User_ID = $GLOBALS['myID'];
$Name = $_POST['Name'];
$UserType = $_POST['UserType'];
$BirthDate = $_POST['BirthDate'];
$PhoneNumber = $_POST['PhoneNumber'];
$Address = $_POST['Address'];
$State = $_POST['State'];
$City = $_POST['City'];
$Zipcode = $_POST['Zipcode'];

//Update
$stmt = $mysqli->prepare("UPDATE `User` Set `Name` = ?, `UserType` = ?, `BirthDate` = ?, `PhoneNumber` = ?, `Address` = ?, `City` = ?, `State` = ?, `Zipcode` = ? WHERE `User_ID` = ? ");
$stmt->bind_param("siiisssis", $Name, $UserType, $BirthDate, $PhoneNumber, $Address, $City, $State, $Zipcode, $User_ID);
$succeed = $stmt->execute();

if ($succeed) {
    die(NoErr());
}
die(ReturnError(2,"Unexpected Unknown Error"));