import Slider from "@react-native-community/slider";
import Checkbox from "expo-checkbox";
import { Formik, Field, Form } from "formik";
import { RadioButton } from "react-native-paper";
import React, { useState, useEffect, useContext } from "react";
import {
  TestDataContext,
  TestDataDispatchContext,
} from "../components/TestDataProvider.js";
import { MaterialCommunityIcons } from "@expo/vector-icons";
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

const MyComponent = () => {
  const [checked, setChecked] = React.useState("first");

  return (
    <View>
      <RadioButton
        value="first"
        status={checked === "first" ? "checked" : "unchecked"}
        onPress={() => setChecked("first")}
      />
      <RadioButton
        value="second"
        status={checked === "second" ? "checked" : "unchecked"}
        onPress={() => setChecked("second")}
      />
    </View>
  );
};

const TimeFilter = (props) => {
  const [modalVisible, setModalVisible] = useState(false);
  const [isEnabled, setIsEnabled] = useState(false);
  const toggleSwitch = () => setIsEnabled((previousState) => !previousState);
  const [lockFilter, setLockFilter] = useState(false);

  function handleApply(numberTests) {
    setModalVisible(false);
    props.handleSubmission(sliderValue);
  }

  let numberTests = 0;
  const testData = React.useContext(TestDataContext);
  const monthValues = [];

  Object.entries(testData).map(([test, value]) => {
    // const diff = new Date() - new Date(value["date"])
    // const months = Math.floor(diff/1000/60/60/24/30)
    // monthValues.push(months)
    // console.log(value["date"], months)
    if (value["display"]) {
      numberTests++;
    }
  });

  const [sliderValue, setSliderValue] = useState(2);

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
        <View>
          <View style={styles.modalView}>
            <View style={{ alignItems: "center" }}>
              <Text style={styles.modalText}>FILTERING OPTIONS</Text>
            </View>
            <View
              style={{
                alignItems: "center",
                justifyContent: "center",
                paddingVertical: 10,
              }}
            >
              <View
                style={{
                  borderColor: "black",
                  borderWidth: 1,
                  padding: 20,
                  borderRadius: 10,
                  justifyContent: "center",
                  alignContent: "center",
                  alignItems: "center"
                }}
              >
                <Slider
                  style={{ width: 200, height: 40 }}
                  minimumValue={2}
                  maximumValue={numberTests}
                  step={1}
                  value={sliderValue}
                  onValueChange={(sliderValue) => setSliderValue(sliderValue)}
                  minimumTrackTintColor="#000000"
                  maximumTrackTintColor="#000000"
                />
                <Text style={{ color: "#000000" }}>
                  Display how many tests? <Text style={{ color: "#000000", fontWeight: "bold" }}>{sliderValue}</Text>
                </Text>
                <Text style={{ color: "#000000" }}>
                </Text>
              </View>
            </View>
            <View
              style={{
                flexDirection: "row",
                alignItems: "center",
                justifyContent: "center",
                paddingVertical: 10,
              }}
            >
              <Button onPress={() => handleApply()} title="Apply"></Button>
              <Button
                onPress={() => setModalVisible(false)}
                title="Cancel"
              ></Button>
            </View>
          </View>
        </View>
      </Modal>
      <Pressable
        style={[styles.button, styles.buttonOpen]}
        onPress={() => setModalVisible(true)}
      >
        <MaterialCommunityIcons name="filter" size={40} color="#fff" />
      </Pressable>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#484d52",
  },
  horizontal: {
    flexDirection: "row",
    alignItems: "flex-end",
    justifyContent: "space-evenly",
    backgroundColor: "#1285b0",
    paddingVertical: 5,
    borderRadius: 100,
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
    backgroundColor: "#69A3BA",
    borderRadius: 20,
    marginBottom: 30,
  },
  text_content: {
    fontSize: 20,
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
});

export default TimeFilter;
