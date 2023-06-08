<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

if (!isset($_POST['title']) || !isset($_POST['details']) || !isset($_POST['cost']) || !isset($_POST['digital'])) {
    die(ReturnError(3,"Incorrect Parameters"));
}

# active will always be set to true, given that the task has just been created
$title = $_POST['title'];
$active = 1;
$details = $_POST['details'];
$authorID = $GLOBALS['myID'];
$digital = $_POST['digital'];
$cost = $_POST['cost'];
$succeed = false;

if (!$digital) {
    if (!isset($_POST['address']) || !isset($_POST['city']) || !isset($_POST['state']) || !isset($_POST['zipcode'])) {
        # The error will occur if it has not recieved address, city, state, or zipcode
        die(ReturnError(3,"Incorrect Parameters"));
    }

    # vars go here as well
    $address = $_POST['address'];
    $city = $_POST['city'];
    $state = $_POST['state'];
    $zipcode = $_POST['zipcode'];

    // Insert 
    $stmt = $mysqli->prepare("INSERT INTO `Task` (`Title`, `Active`, `Details`, `Author_ID_FK`, `Cost`, `Digital`,`Address`, `City`, `State`, `Zipcode`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    //printf("Error message: %s\n", $mysqli->error);

    $stmt->bind_param("sisidisssi", $title, $active, $details, $authorID, $cost, $digital, $address, $city, $state, $zipcode);
    $succeed = $stmt->execute();
} else {
    // Insert 
    $stmt = $mysqli->prepare("INSERT INTO `Task` (`Title`, `Active`, `Details`, `Author_ID_FK`,`Cost`, `Digital`) VALUES (?, ?, ?, ?, ?, ?);");
    $stmt->bind_param("sisidi", $title, $active, $details, $authorID, $cost, $digital);
    $succeed = $stmt->execute();
}

if ($succeed) {
    die(NoErr());
}
die(ReturnError(2,"Unexpected Unknown Error"));