import { MaterialCommunityIcons } from '@expo/vector-icons';
import Slider from '@react-native-community/slider';
import Checkbox from 'expo-checkbox';
import { Formik, Field, Form } from "formik";
import React, { useState, useEffect} from "react";
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

const CheckBoxLock = ({ children, value, handleChange }) => {

  return (
    <View>
      <View
        style={{
          flexDirection: "row",
          alignItems: "center",
          justifyContent: "center",
          paddingVertical: 10,
        }}
      >
        <Checkbox
          type={"checkbox"}
          value={value}
          onValueChange={handleChange}
          //   {...props}
          style={{ width: 26, height: 26 }}
        />
        <Text> </Text>
        <Text>{children}</Text>
      </View>
    </View>
  );


}

const CheckBox = ({ children, value, handleChange, lockFilter}) => {

  return (
    <View>
      <View
        style={{
          flexDirection: "row",
          alignItems: "center",
          justifyContent: "center",
          paddingVertical: 10,
        }}
      >
        {lockFilter ? (
          <Checkbox
            disabled
            type={"checkbox"}
            // value={value}
            onValueChange={handleChange}
            //   {...props}
            style={{ width: 26, height: 26 }}
          />
        ) : (
          <Checkbox
            type={"checkbox"}
            value={value}
            onValueChange={handleChange}
            //   {...props}
            style={{ width: 26, height: 26 }}
          />
        )}
        <Text> </Text>
        <Text>{children}</Text>
      </View>
    </View>
  );
};

var Filter = (props) => {
  const [modalVisible, setModalVisible] = useState(false);
  const [isEnabled, setIsEnabled] = useState(false);
  const toggleSwitch = () => setIsEnabled((previousState) => !previousState);
  const [sliderValue, setSliderValue] = useState(1);
  const [lockFilter, setLockFilter] = useState(false);

  const handleCancel = () => {
    setModalVisible(!modalVisible)
    setLockFilter(false);
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
              <Formik
                initialValues={{
                  A: false,
                  C: false,
                  D: false,
                  E: false,
                  K: false,
                  Calcium: false,
                  Choline: false,
                  Iron: false,
                  Magnesium: false,
                  Phosphorus: false,
                  Potassium: false,
                  Sodium: false,
                  Zinc: false,
                  showAll: false,
                  sortPriority: false,
                }}
                onSubmit={(values, { resetForm }) => {
                  Object.entries(values).map(([key, value]) => {
                    if (key == "sortPriority") {
                      return;
                    }
                    if (value) {
                      
                      props.handleChangeBiomarkers(values);
                      setModalVisible(!modalVisible);
                      return;
                    }
                  });

                  setModalVisible(!modalVisible);
                  setLockFilter(false);
                }}
              >
                {({ handleChange, handleSubmit, values, setFieldValue }) => (
                  <View>
                    <View
                      style={{
                        borderColor: "black",
                        borderWidth: 1,
                        padding: 20,
                        borderRadius: 10,
                      }}
                    >
                      <View style={{ alignItems: "center" }}>
                        <Text style={styles.modalHeader}>BIOMARKERS</Text>
                      </View>

                      <View style={styles.horizontalFilter}>
                        <View style={{ paddingRight: 8 }}>
                          <CheckBox
                            value={values?.A}
                            handleChange={(nextValue) =>
                              setFieldValue("A", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Vitamin A
                          </CheckBox>
                        </View>
                        <View style={{ paddingLeft: 8 }}>
                          <CheckBox
                            value={values?.C}
                            handleChange={(nextValue) =>
                              setFieldValue("C", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Vitamin C
                          </CheckBox>
                        </View>
                      </View>
                      <View style={styles.horizontalFilter}>
                        <View style={{ paddingRight: 8 }}>
                          <CheckBox
                            value={values?.D}
                            handleChange={(nextValue) =>
                              setFieldValue("D", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Vitamin D
                          </CheckBox>
                        </View>
                        <View style={{ paddingLeft: 8 }}>
                          <CheckBox
                            value={values?.E}
                            handleChange={(nextValue) =>
                              setFieldValue("E", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Vitamin E
                          </CheckBox>
                        </View>
                      </View>
                      <View style={styles.horizontalFilter}>
                        <View style={{ paddingRight: 10 }}>
                          <CheckBox
                            value={values?.K}
                            handleChange={(nextValue) =>
                              setFieldValue("K", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Vitamin K{" "}
                          </CheckBox>
                        </View>
                        <View style={{ paddingRight: 11 }}>
                          <CheckBox
                            value={values?.Sodium}
                            handleChange={(nextValue) =>
                              setFieldValue("Sodium", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Sodium
                          </CheckBox>
                        </View>
                      </View>
                      <View style={styles.horizontalFilter}>
                        <View style={{ paddingRight: 15 }}>
                          <CheckBox
                            value={values?.Calcium}
                            handleChange={(nextValue) =>
                              setFieldValue("Calcium", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Calcium{" "}
                          </CheckBox>
                        </View>
                        <View style={{ paddingLeft: 2, paddingRight: 10 }}>
                          <CheckBox
                            value={values?.Choline}
                            handleChange={(nextValue) =>
                              setFieldValue("Choline", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Choline
                          </CheckBox>
                        </View>
                      </View>
                      <View style={styles.horizontalFilter}>
                        <View style={{ paddingLeft: 18, paddingRight: 2 }}>
                          <CheckBox
                            value={values?.Iron}
                            handleChange={(nextValue) =>
                              setFieldValue("Iron", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Iron {"             "}
                          </CheckBox>
                        </View>
                        <View style={{ paddingLeft: 10, paddingRight: 0 }}>
                          <CheckBox
                            value={values?.Magnesium}
                            handleChange={(nextValue) =>
                              setFieldValue("Magnesium", nextValue)
                            }
                            lockFilter={lockFilter}
                          >
                            Magnesium
                          </CheckBox>
                        </View>
                      </View>
                      <CheckBoxLock
                        value={values?.showAll}
                        handleChange={(nextValue) => {
                          setFieldValue("showAll", nextValue);
                          setLockFilter(!lockFilter);
                        }}
                        lockFilter={lockFilter}
                      >
                        Show All Biomarkers
                      </CheckBoxLock>
                    </View>
                    <View
                      style={{
                        borderColor: "black",
                        borderWidth: 1,
                        padding: 20,
                        borderRadius: 10,
                        marginTop: 10,
                      }}
                    >
                      <View style={{ alignItems: "center" }}>
                        <Text style={styles.modalHeader}>ABNORMALITY</Text>
                        <CheckBox
                          value={values?.sortPriority}
                          handleChange={(nextValue) =>
                            setFieldValue("sortPriority", nextValue)
                          }
                        >
                          Filter by Abnormality
                        </CheckBox>
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
                      <Button onPress={handleSubmit} title="Apply"></Button>
                      <Button
                        onPress={() => handleCancel()}
                        title="Cancel"
                      ></Button>
                    </View>
                  </View>
                )}
              </Formik>
            </View>
          </View>
        </View>
      </Modal>
      <Pressable
        style={[styles.button, styles.buttonOpen]}
        onPress={() => setModalVisible(true)}
      >
        <MaterialCommunityIcons name="filter" size={40} color="white" />
      </Pressable>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#466B7A",
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
    marginVertical: 175,
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
  modalHeader: {
    fontSize: 13,
    fontWeight: "600",
    marginBottom: 10,
  },
  button: {
    // borderRadius: 10,
    // elevation: 2
  },
  horizontalFilter: {
    flexDirection: "row",
    alignItems: "flex-end",
    justifyContent: "space-evenly"
  },
  buttonClose: {
    //backgroundColor: "#2196F3",
  },
});

export default Filter;