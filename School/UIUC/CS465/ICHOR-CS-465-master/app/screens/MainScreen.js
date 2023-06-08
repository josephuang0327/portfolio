import { Formik, Field, Form } from "formik";
import React, { useState, useEffect } from "react";
import {
  Button,
  Text,
  Switch,
  StyleSheet,
  SafeAreaView,
  ScrollView,
  View,
  Image,
  TouchableOpacity,
  Alert,
  Modal,
  Pressable,
  Dimensions,
} from "react-native";

import { BarChart } from "react-native-chart-kit";

import { XAxis } from "react-native-svg-charts";

import Filter from "../components/Filter.js";
import { MaterialIcons, Octicons, Foundation } from "@expo/vector-icons";
import {
  TestDataContext,
  TestDataDispatchContext,
} from "../components/TestDataProvider.js";
import {
  BiomarkerContext,
  BiomarkerDispatchContext,
} from "../components/BiomarkerProvider.js";
import { BiomarkerInfoContext } from "../components/BiomarkerInfoProvider.js";
import {
  ImportVisitedContext,
  ImportVisitedDispatchContext,
} from "../components/ImportVisitedContext.js";

export default function MainScreen({ navigation }) {
  let MainScreenJSON = require("../assets/main-screen.json");
  let stringData = JSON.stringify(MainScreenJSON);
  const data = JSON.parse(stringData);
  const [biomarkers, setBiomarkers] = useState(data);
  const [displayBiomarkers, setDisplayBiomarkers] = useState({ ...biomarkers });
  // const [alert, setAlert] = useState(false)
  const setBiomarker = React.useContext(BiomarkerDispatchContext);
  const biomarkerInfo = React.useContext(BiomarkerInfoContext);
  const initializeTestData = React.useContext(TestDataContext);
  const [testData, setTestData] = useState(initializeTestData);

  const importVisited = React.useContext(ImportVisitedContext);
  const setImportVisited = React.useContext(ImportVisitedDispatchContext);

  let biomarkersCopy = biomarkers;

  // if (importVisited) {
  //   setImportVisited(false);
  //   let biomarkersCopy = biomarkers;

  //   Object.entries(biomarkersCopy).map(([key, value]) => {
  //     biomarkersCopy[key]["display"] = true;
  //     biomarkersCopy[key]["alert"] = false;
  //   });
  // }

  Object.entries(biomarkersCopy).map(([key, value]) => {
    biomarkersCopy[key]["warning"] = false;
  });

  compareTests = [];

  Object.entries(testData).map(([test, value]) => {
    if (value["display"]) {
      compareTests.push(value);
    }
  });

  // console.log(alert)

  const [currentTest] = compareTests;
  Object.entries(currentTest["data"]).map(([biomarker, value]) => {
    const range = biomarkerInfo[biomarker]["range"];
    // console.log(biomarker, range)
    if (value < range[0] || value > range[1]) {
      // console.log(value, range[0], range[1]);
      biomarkersCopy[biomarker]["warning"] = true;
      // console.log(biomarkersCopy[biomarker]);
    }
  });

  function handleChangeBiomarkers(biomarker) {
    // let biomarkersCopy = biomarkers;
    let objects = Object.entries(biomarker);

    let alert = false;

    if (
      objects[objects.length - 1][0] == "sortPriority" &&
      objects[objects.length - 1][1] == true
    ) {
      alert = true;
    }

    //remove sortPriority from object entries
    objects.pop();

    if (
      objects[objects.length - 1][0] == "showAll" &&
      objects[objects.length - 1][1] == true
    ) {
      Object.entries(biomarkersCopy).map(([key, value]) => {
        biomarkersCopy[key]["display"] = true;
        biomarkersCopy[key]["alert"] = false;
      });
      setBiomarkers({ ...biomarkersCopy });
    } else {
      Object.entries(biomarkersCopy).map(([key, value]) => {
        if (key != "showAll") {
          biomarkersCopy[key]["display"] = false;
          biomarkersCopy[key]["alert"] = false;
        }
      });

      objects.map(([key, value]) => {
        if (key != "showAll") {
          biomarkersCopy[key]["display"] = value;
        }
      });
    }
    compareTests = [];

    Object.entries(testData).map(([test, value]) => {
      if (value["display"]) {
        compareTests.push(value);
      }
    });

    // console.log(alert)

    if (alert) {
      const [currentTest] = compareTests;
      Object.entries(currentTest["data"]).map(([biomarker, value]) => {
        const range = biomarkerInfo[biomarker]["range"];
        // console.log(biomarker, range)
        if (value < range[0] || value > range[1]) {
          // console.log(value, range[0], range[1]);
          biomarkersCopy[biomarker]["alert"] = true;
          // console.log(biomarkersCopy[biomarker]);
        }
      });
    }

    setBiomarkers({ ...biomarkersCopy });
  }

  function handleGraphView(biomarker) {
    setBiomarker(biomarker);
    navigation.navigate("Graph");
  }

  return (
    <SafeAreaView style={styles.container}>
      <View style={{ paddingHorizontal: 30, paddingVertical: 10 }}>
        <View style={styles.horizontal}>
          <Filter
            biomarkers={biomarkers}
            handleChangeBiomarkers={(biomarker) =>
              handleChangeBiomarkers(biomarker)
            }
            defaultAllBiomarkers={() => defaultAllBiomarkers()}
          />
          <TouchableOpacity onPress={() => navigation.navigate("LogIn")}>
            <MaterialIcons name="person" size={40} color="white" />
          </TouchableOpacity>
          <TouchableOpacity onPress={() => navigation.navigate("Import")}>
            <MaterialIcons name="upload-file" size={40} color="white" />
          </TouchableOpacity>
        </View>
      </View>
      <ScrollView style={styles.scroll_view}>
        {Object.entries(biomarkers).map(([key, value]) => {
          return (
            value["display"] &&
            value["alert"] && (
              <View style={styles.card_element} key={key}>
                <View
                  style={{
                    flexDirection: "row",
                    alignItems: "flex-end",
                    justifyContent: "space-between",
                    padding: 10,
                  }}
                >
                  <Text style={styles.text_content}>{value.name}</Text>
                  <Info>{value.info}</Info>
                </View>
                <View style={styles.center}>
                  <StackedBarChart testData={testData} biomarker={key} />
                  <View style={{ marginTop: 5, marginBottom: 10 }}>
                    <Text style={styles.text_content_range}>
                      Ideal range: {biomarkerInfo[key]["range"][0]} -{" "}
                      {biomarkerInfo[key]["range"][1]}{" "}
                      {biomarkerInfo[key]["units"]}
                    </Text>
                    {value["warning"] && (
                      <View
                        style={{
                          flexDirection: "row",
                          alignItems: "flex-end",
                          // justifyContent: "space-between",
                        }}
                      >
                        <MaterialIcons
                          name="error-outline"
                          size={20}
                          color="orange"
                        />
                        <Text style={styles.text_content_range}>
                          {" "}
                          Recent test out of range
                        </Text>
                      </View>
                    )}
                  </View>
                  <TouchableOpacity onPress={() => handleGraphView(key)}>
                    <View
                      style={{
                        flexDirection: "row",
                        backgroundColor: "#484d52",
                        padding: 5,
                        borderRadius: 5,
                      }}
                    >
                      <Octicons
                        name="graph"
                        size={16}
                        color="white"
                        style={{ marginRight: 5 }}
                      />
                      <Text style={styles.textButtons}>Breakdown</Text>
                    </View>
                  </TouchableOpacity>
                </View>
              </View>
            )
          );
        })}
        {Object.entries(displayBiomarkers).map(([key, value]) => {
          return (
            value["display"] &&
            !value["alert"] && (
              <View style={styles.card_element} key={key}>
                <View
                  style={{
                    flexDirection: "row",
                    alignItems: "flex-end",
                    justifyContent: "space-between",
                    padding: 10,
                  }}
                >
                  <Text style={styles.text_content}>{value.name}</Text>
                  <Info>{value.info}</Info>
                </View>
                <View style={styles.center}>
                  <StackedBarChart testData={testData} biomarker={key} />
                  <View style={{ marginTop: 5, marginBottom: 10 }}>
                    <Text style={styles.text_content_range}>
                      Ideal Range: {biomarkerInfo[key]["range"][0]} -{" "}
                      {biomarkerInfo[key]["range"][1]}{" "}
                      {biomarkerInfo[key]["units"]}
                    </Text>
                    {value["warning"] && (
                      <View
                        style={{
                          flexDirection: "row",
                          alignItems: "flex-end",
                          // justifyContent: "space-between",
                        }}
                      >
                        <MaterialIcons
                          name="error-outline"
                          size={20}
                          color="orange"
                        />
                        <Text style={styles.text_content_range}>
                          {" "}
                          Recent test out of range
                        </Text>
                      </View>
                    )}
                  </View>
                  <TouchableOpacity onPress={() => handleGraphView(key)}>
                    <View
                      style={{
                        flexDirection: "row",
                        backgroundColor: "#484d52",
                        padding: 5,
                        borderRadius: 5,
                      }}
                    >
                      <Octicons
                        name="graph"
                        size={16}
                        color="white"
                        style={{ marginRight: 5 }}
                      />
                      <Text style={styles.textButtons}>Breakdown</Text>
                    </View>
                  </TouchableOpacity>
                </View>
              </View>
            )
          );
        })}
      </ScrollView>
    </SafeAreaView>
  );
}

var Info = (info) => {
  const [modalVisible, setModalVisible] = useState(false);
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
        <View>
          <View style={styles.modalView}>
            <Text style={styles.modalText}>{info.children}</Text>
            <View style={{ alignItems: "center" }}>
              <Pressable
                style={[styles.button, styles.buttonClose]}
                onPress={() => setModalVisible(!modalVisible)}
              >
                <Text style={{ color: "blue", fontSize: 18 }}>Close</Text>
              </Pressable>
            </View>
          </View>
        </View>
      </Modal>
      <Pressable
        style={[styles.button, styles.buttonOpen]}
        onPress={() => setModalVisible(true)}
      >
        <Foundation name="info" size={29} color="white" />
      </Pressable>
    </View>
  );
};

const StackedBarChart = ({ testData, biomarker }) => {
  compareTests = [];

  Object.entries(testData).map(([test, value]) => {
    if (value["display"]) {
      compareTests.push(value);
    }
  });

  const [currentTest, previousTest] = compareTests;

  const currentDataLabel = currentTest["date"];
  const previousDataLabel = previousTest["date"];
  const currentDataPoint = currentTest["data"][biomarker];
  const previousDataPoint = previousTest["data"][biomarker];
  const biomarkerInfo = React.useContext(BiomarkerInfoContext);
  const range1 = biomarkerInfo[biomarker]["range"];

  const lower = range1[0];
  const higher = range1[1];

  if (lower < previousDataPoint && previousDataPoint < higher) {
    colorp = "#b3dee2";
  } else {
    colorp = "#fc6203";
  }
  if (lower < currentDataPoint && currentDataPoint < higher) {
    colorc = "#b3dee2";
  } else {
    colorc = "#fc6203";
  }

  return (
    <>
      <BarChart
        style={{
          marginVertical: 8,
          borderRadius: 20,
          shadowOpacity: 0.5,
          shadowOffset: { height: 1 },
        }}
        data={{
          labels: [`${previousDataLabel}`, `${currentDataLabel}`],
          datasets: [
            {
              data: [previousDataPoint, currentDataPoint],
              colors: [(opacity = 1) => colorp, (opacity = 1) => colorc],
            },
          ],
        }}
        fromZero={true}
        width={250}
        height={220}
        chartConfig={{
          backgroundColor: "#1cc910",
          backgroundGradientFrom: "#eff3ff",
          backgroundGradientTo: "#efefef",
          decimalPlaces: 2,
          color: (opacity = 1) => `rgba(1, 73, 105, ${opacity})`,
        }}
        withCustomBarColorFromData={true}
        flatColor={true}
      />
    </>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#D3D3D3",
  },
  horizontal: {
    flexDirection: "row",
    alignItems: "flex-end",
    justifyContent: "space-evenly",
    backgroundColor: "#4895d9",
    paddingVertical: 5,
    borderRadius: 100,
    shadowOpacity: 0.5,
    shadowOffset: { height: 1 },
  },
  heading: {
    color: "#fff",
    fontSize: 25,
    fontWeight: "600",
    marginTop: 30,
    marginBottom: 10,
    textAlign: "center",
  },
  scroll_view: {
    padding: 30,
  },
  card_element: {
    padding: 10,
    backgroundColor: "#4895d9",
    borderRadius: 20,
    marginBottom: 30,
    shadowOpacity: 0.5,
    shadowOffset: { height: 1 },
  },
  text_content: {
    fontSize: 20,
    color: "white",
    fontWeight: "600",
  },
  text_content_range: {
    fontSize: 16,
    color: "white",
    fontWeight: "600",
  },
  tinyLogo: {
    width: 38,
    height: 38,
  },
  moretinyLogo: {
    width: 25,
    height: 25,
  },
  center: {
    alignItems: "center",
    justifyContent: "center",
  },
  modalView: {
    marginHorizontal: 20,
    marginVertical: 200,
    backgroundColor: "white",
    borderRadius: 20,
    padding: 20,
    //alignItems: "center",
    shadowColor: "#000",
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowOpacity: 0.25,
    shadowRadius: 4,
    elevation: 5,
  },
  modalText: {
    fontSize: 15,
    fontWeight: "600",
    marginBottom: 10,
  },
  button: {
    // borderRadius: 10,
    // elevation: 2
  },
  buttonClose: {
    //backgroundColor: "#2196F3",
  },
  textButtons: {
    color: "#fff",
    fontWeight: "800",
    fontSize: 14,
  },
});
