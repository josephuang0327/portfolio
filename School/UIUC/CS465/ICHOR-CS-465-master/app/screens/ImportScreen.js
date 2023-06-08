import {
  Image,
  Alert,
  Modal,
  StyleSheet,
  Text,
  Pressable,
  View,
  SafeAreaView,
} from "react-native";
import React, { useState } from "react";
import bloodTestData from "../assets/bloodtest.json";
import { MaterialIcons } from "@expo/vector-icons";
import styled from "styled-components";
import {TestDataContext, TestDataDispatchContext} from "../components/TestDataProvider.js";
import {BiomarkerInfoContext, BiomarkerInfoDispatchContext} from "../components/BiomarkerInfoProvider.js"
import {ImportVisitedDispatchContext} from "../components/ImportVisitedContext.js"

function Header(props) {
  return (
    <View style={styles.horizontal}>
      <AddTestModal
        handleAddTest={() => props.handleAddTest()}
        mostRecent={props.mostRecent}
      />
    </View>
  );
}

const Import = ({navigation}) => {

  const testData = React.useContext(TestDataContext);
  const setTestData = React.useContext(TestDataDispatchContext);
  // const importVisited = React.useContext(ImportVisitedContext)
  const setImportVisited = React.useContext(ImportVisitedDispatchContext);
  const [mostRecent, setMostRecent] = useState(false);

  function handleRemoveTest(test) {
    let testDataCopy = Object.assign({}, testData, {});
    testDataCopy[test]["display"] = false;
    setTestData(testDataCopy);
    console.log("remove")
    setImportVisited(true);
  }

  function handleAddTest() {
    let testDataCopy = Object.assign({}, testData, {});
    testDataCopy["test_recent"]["display"] = true;
    setTestData(testDataCopy);
    setMostRecent(true);
    setImportVisited(true);
  }

  return (
    <SafeAreaView style={styles.container}>
      <Header handleAddTest={() => handleAddTest()} mostRecent={mostRecent} />
      <ComponentContainer>
        <TestListDisplay
          testData={testData}
          handleRemoveTest={(test) => handleRemoveTest(test)}
        />
      </ComponentContainer>
    </SafeAreaView>
  );
}

class TestListDisplay extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      testData: props.testData,
    };
  }

  render() {
    return (
      <ImportListScrollView>
        <View>
          {Object.entries(this.state.testData).map(
            ([test, value]) =>
              value["display"] && (
                <ComponentContainer key={value.id}>
                  <ListContainer>
                    <PreviewTestModal>{value["data"]}</PreviewTestModal>
                    <View>
                      <TextItem>{value["date"]}</TextItem>
                      {/* <TextDate>{value["date"]}</TextDate> */}
                    </View>
                    <RemoveTestWarningModal
                      test={test}
                      handleRemoveTest={(test) =>
                        this.props.handleRemoveTest(test)
                      }
                    />
                  </ListContainer>
                </ComponentContainer>
              )
          )}
        </View>
      </ImportListScrollView>
    );
  }
}

const RemoveTestWarningModal = (props) => {
  const [modalVisible, setModalVisible] = useState(false);

  function Confirm() {
    setModalVisible(!modalVisible);
    props.handleRemoveTest(props.test);
  }

  return (
    <View style={styles.centeredView}>
      <Modal
        animationType="slide"
        transparent={true}
        visible={modalVisible}
        onRequestClose={() => {
          Alert.alert("Modal has been closed.");
          setModalVisible(!modalVisible);
        }}
      >
        <View style={styles.centeredView}>
          <View style={styles.modalView}>
            <View style={styles.row}>
              <Text style={styles.modalText}>
                Warning: Are you sure you want to permanently remove this test
                from Ichor?
              </Text>
              <Pressable
                style={[styles.confirmButton, styles.buttonClose]}
                onPress={() => Confirm()}
              >
                <Text style={styles.textStyle}>Confirm</Text>
              </Pressable>
              <Pressable
                style={[styles.cancelButton, styles.buttonClose]}
                onPress={() => setModalVisible(!modalVisible)}
              >
                <Text style={styles.textStyle}>Cancel</Text>
              </Pressable>
            </View>
          </View>
        </View>
      </Modal>
      <IconContainer onPress={() => setModalVisible(true)}>
        <MaterialIcons name="delete" size={28} color="#484d52" />
      </IconContainer>
    </View>
  );
};

const AddTestModal = (props) => {
  const [modalVisible, setModalVisible] = useState(false);

  function Confirm() {
    setModalVisible(!modalVisible);
    props.handleAddTest();
  }

  return (
    <View>
      <Modal
        animationType="slide"
        transparent={true}
        visible={modalVisible}
        onRequestClose={() => {
          Alert.alert("Modal has been closed.");
          setModalVisible(!modalVisible);
        }}
      >
        <View style={styles.centeredView}>
          <View style={styles.modalView}>
            {/* Conditional Rendering */}
            {!props.mostRecent && (
              <View style={styles.row}>
                <Text style={styles.modalText}>
                  Import latest blood test from MyChart?
                </Text>
                <Pressable
                  style={[styles.confirmButton, styles.buttonClose]}
                  onPress={() => Confirm()}
                >
                  <Text style={styles.textStyle}>Confirm</Text>
                </Pressable>
                <Pressable
                  style={[styles.cancelButton, styles.buttonClose]}
                  onPress={() => setModalVisible(!modalVisible)}
                >
                  <Text style={styles.textStyle}>Cancel</Text>
                </Pressable>
              </View>
            )}
            {props.mostRecent && (
              <View style={styles.row}>
                <Text style={styles.modalText}>
                  Notice: There are currently no recent tests to import from
                  MyChart.
                </Text>
                <Pressable
                  style={[styles.okButton, styles.buttonClose]}
                  onPress={() => setModalVisible(!modalVisible)}
                >
                  <Text style={styles.textStyle}>Ok</Text>
                </Pressable>
              </View>
            )}
          </View>
        </View>
      </Modal>
      <IconContainer onPress={() => setModalVisible(true)}>
        <MaterialIcons name="add-circle-outline" size={32} color="#484d52" />
      </IconContainer>
    </View>
  );
};

var PreviewTestModal = (data) => {
  const biomarkerInfo = React.useContext(BiomarkerInfoContext);

  const [modalVisible, setModalVisible] = useState(false);
  var dataStringified = JSON.stringify(data.children);
  dataStringified = dataStringified.replace(/['"{}]+/g, '');
  dataStringified = dataStringified.split(",").join("\n");

  const dataDisplay = [];
  Object.entries(data["children"]).map(([key, value]) => {
    const units = biomarkerInfo[key]["units"];
    dataDisplay.push(key + ": " + value + " " + units)
  })

  return (
    <View>
      <Modal
        style={{ marginTop: 50 }}
        animationType="slide"
        transparent={true}
        visible={modalVisible}
        onRequestClose={() => {
          Alert.alert("Modal has been closed.");
          setModalVisible(!modalVisible);
        }}
      >
        <View style={styles.centeredView}>
          <View style={styles.modalView}>
            <Text style={[styles.headerText, styles.bloodTestModalPadding]}>
              Blood Test Preview
            </Text>
            {dataDisplay.map((value) => 
              <Text style={styles.modalText}>{value}</Text>
            )}
            <View style={{ alignItems: "center" }}>
              <Pressable
                style={[styles.okButton, styles.buttonClose]}
                onPress={() => setModalVisible(!modalVisible)}
              >
                <Text style={styles.textStyle}>Close</Text>
              </Pressable>
            </View>
          </View>
        </View>
      </Modal>
      <IconContainer onPress={() => setModalVisible(true)}>
        <CircleContainer>
          <MaterialIcons name="description" size={32} color="#484d52" />
        </CircleContainer>
      </IconContainer>
    </View>
  );
};

const styles = StyleSheet.create({
  safeView: {
    backgroundColor: "#d3d3d3",
  },
  cancelButton: {
    backgroundColor: "#d3d3d3",
    borderRadius: 20,
    padding: 10,
    elevation: 2,
    marginLeft: 10,
  },
  confirmButton: {
    backgroundColor: "#d3d3d3",
    borderRadius: 20,
    padding: 10,
    elevation: 2,
  },
  container: {
    flex: 1,
    backgroundColor: "#D3D3D3",
  },
  title: {
    textAlign: "center",
    marginVertical: 8,
    backgroundColor: "#f0f8ff",
    height: 50,
  },
  fixToText: {
    flexDirection: "row",
    justifyContent: "space-between",
  },
  separator: {
    marginVertical: 8,
    borderBottomColor: "#737373",
    borderBottomWidth: 1,
  },
  centeredView: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    marginTop: 22,
  },
  modalView: {
    margin: 20,
    backgroundColor: "white",
    borderRadius: 20,
    padding: 35,
    alignItems: "center",
    shadowColor: "#000",
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowOpacity: 0.25,
    shadowRadius: 4,
    elevation: 5,
  },
  button: {
    padding: 10,
    elevation: 2,
    height: 20,
    marginBottom: 30,
  },
  buttonOpen: {
    backgroundColor: "#F194FF",
  },
  buttonClose: {
    backgroundColor: "#484d52",
  },
  textStyle: {
    color: "white",
    fontWeight: "bold",
    textAlign: "center",
  },
  modalText: {
    marginBottom: 15,
    textAlign: "center",
    fontSize: 18,
    justifyContent: "center"
  },
  headerText: {
    marginBottom: 15,
    textAlign: "center",
    fontSize: 18,
    justifyContent: "center",
    fontWeight: "bold"
  },
  row: {
    flexDirection: "row",
    flexWrap: "wrap",
    textAlign: "center",
    justifyContent: "center",
  },

  importListScrollView: {
    borderColor: "white",
    borderWidth: 1,
  },

  horizontal: {
    flexDirection: "row",
    alignItems: "flex-end",
    justifyContent: "flex-end",
    backgroundColor: "#D3D3D3",
    marginRight: 20
  },
  heading: {
    color: "#fff",
    fontSize: 32,
    fontWeight: "600",
    marginTop: 60,
    marginBottom: 10,
    textAlign: "center",
  },
  okButton: {
    backgroundColor: "#d3d3d3",
    borderRadius: 20,
    padding: 10
  },
  bloodTestModalPadding: {
    paddingHorizontal:50
  }
});

const PressableAddTest = styled(Pressable)`
  color: white;
  border-radius: 20px;
`;

const ImportListScrollView = styled.ScrollView`
  height: 80%;
  border-width: 1px;
  border-top-color: #484d52;
  border-top-width: 1px;
  border-bottom-color: #484d52;
  border-bottom-width: 1px;
  margin-bottom: 40px;
`;

const ListContainer = styled.View`
  height: auto;
  width: 100%;
  flex-direction: row;
  justify-content: space-between;
  border-bottom-color: #484d52;
  border-bottom-width: 1px;
`;

const ComponentContainer = styled.View`
  flex-direction: row;
  justify-content: center;
  height: auto;
  width: auto;
`;

const AddTestModalContainer = styled.View`
  flex-direction: row;
  justify-content: flex-end;
  align-items: center;
  height: auto;
  width: auto;
  margin-right: 10px;
`;

const TextItem = styled.Text`
  color: #484d52;
  width: 240px;
  height: auto;
  font-size: 20px;
  margin-top: 18px;
  margin-right: 20px;
  margin-left: 10px;
`;

const IconContainer = styled.TouchableOpacity`
  height: 40px;
  
`;

const CircleContainer = styled.View`
  height: 40px;
  justify-content: center;
  align-items: center;
  align-content: center;
  margin-top: 10px;
  margin-left: 10px;
  border-radius: 20px;
  border-color: #484d52;
  border-width: 1px;
`;

export default Import;
