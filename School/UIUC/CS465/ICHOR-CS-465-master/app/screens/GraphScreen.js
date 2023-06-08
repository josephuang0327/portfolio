// import React in our code
import React, { useContext, useState } from "react";
// import all the components we are going to use
import {
  SafeAreaView,
  Text,
  View,
  StyleSheet,
  Dimensions,
  ScrollView,
  TouchableOpacity,
  Image,
} from "react-native";

//import React Native chart Kit for different kind of Chart
import { LineChart } from "react-native-chart-kit";

import TimeFilter from "../components/TimeFilter.js";

import {
  TestDataContext,
  TestDataDispatchContext,
} from "../components/TestDataProvider.js";
import { BiomarkerContext } from "../components/BiomarkerProvider.js";
import { BiomarkerInfoContext } from "../components/BiomarkerInfoProvider.js";

const BiomarkerLineChart = (props) => {
  const biomarker = React.useContext(BiomarkerContext);
  const loadedData = [];
  props.compareTests.map((value) => {
    loadedData.push(value["data"][biomarker]);
  });

  const biomarkerInfo = React.useContext(BiomarkerInfoContext);
  const biomarkerName = biomarkerInfo[biomarker]["name"];
  const biomarkerUnits = biomarkerInfo[biomarker]["units"];
  const c = loadedData.reverse();
  const range1 = biomarkerInfo[biomarker]["range"];

  const lower = range1[0];
  const higher = range1[1];

  //TODO: Get units from biomarkerInfo,
  //display healthy range at top of graph with units,
  //change color of line graph dots depending if value is in healthy range

  return (
    <>
      <LineChart
        data={{
          labels: props.labels.reverse(),
          datasets: [
            {
              data: c,
              strokeWidth: 2,
            },
          ],
        }}
        getDotColor={(c) => {
          if (lower < c && c < higher) return "#63e9f2";
          else return "#ff0000"; // orange
        }}
        width={Dimensions.get("window").width - 16}
        height={220}
        yAxisLabel={""}
        chartConfig={{
          backgroundColor: "#1cc910",
          backgroundGradientFrom: "#eff3ff",
          backgroundGradientTo: "#efefef",
          decimalPlaces: 2,
          color: (opacity = 1) => `rgba(1, 73, 105, ${opacity})`,
        }}
        withCustomBarColorFromData={true}
        flatColor={true}
        style={{
          marginVertical: 8,
          borderRadius: 16,
          shadowOpacity: 0.5,
          shadowOffset: { height: 1 },
        }}
      />
    </>
  );
};

const App = ({ navigation }) => {
  const biomarker = React.useContext(BiomarkerContext);
  const biomarkerInfo = React.useContext(BiomarkerInfoContext);

  const testData = React.useContext(TestDataContext);
  let defaultNumberTests = 0;
  Object.entries(testData).map(([test, value]) => {
    if (value["display"]) {
      defaultNumberTests++;
    }
  });

  const [numberTests, setNumberTests] = useState(defaultNumberTests);

  const handleSubmission = (number) => {
    setNumberTests(number);
  };

  let pushedTests = 0;
  let compareTests = [];
  const labels = [];

  Object.entries(testData).map(([test, value]) => {
    if (pushedTests != numberTests) {
      if (value["display"]) {
        if (pushedTests === 0 || pushedTests === numberTests - 1) {
          labels.push(value["date"]);
        } else {
          labels.push("");
        }
        compareTests.push(value);
        pushedTests++;
      }
    }
  });

  const biomarkerName = biomarkerInfo[biomarker]["name"];
  const biomarkerUnits = biomarkerInfo[biomarker]["units"];

  const range1 = biomarkerInfo[biomarker]["range"];

  const lower = range1[0];
  const higher = range1[1];

  return (
    <SafeAreaView style={{ flex: 1, backgroundColor: "#D3D3D3" }}>
      <View style={{ paddingHorizontal: 30, paddingVertical: 5 }}></View>
      <ScrollView style={{ paddingHorizontal: 30 }}>
        <View style={styles.card_element_header}>
          <View
            style={{
              flexDirection: "row",
              alignItems: "center",
              justifyContent: "space-between",
              marginTop: 10,
              paddingHorizontal: 10,
            }}
          >
            <Text style={styles.header_content_top}>
              {biomarkerName} ({biomarkerUnits})
            </Text>
            <TimeFilter
              handleSubmission={(numberTests) => handleSubmission(numberTests)}
              biomarker={biomarker}
            />
          </View>
          <View
            style={{
              flexDirection: "row",
              alignItems: "center",
              justifyContent: "",
              marginBottom: 5,
              paddingHorizontal: 10,
              marginLeft: 11
            }}
          >
            <Text style={styles.text_content}>
              Ideal Range: {lower} - {higher} ({biomarkerUnits})
            </Text>
          </View>
        </View>
        <View style={styles.container}>
          <View>
            <BiomarkerLineChart compareTests={compareTests} labels={labels} />
          </View>
        </View>
        <View style={styles.card_element}>
          <View
            style={{
              flexDirection: "column",
              alignItems: "flex-start",
              justifyContent: "space-between",
              padding: 10,
            }}
          >
            <Text style={styles.header_content}>Daily Requirement:</Text>
            <Text style={styles.text_content}>
              Men: {biomarkerInfo[biomarker]["requirementsMen"]} {"\n"}
              Women: {biomarkerInfo[biomarker]["requirementsWomen"]}
            </Text>
          </View>
        </View>
        <View style={styles.card_element}>
          <View
            style={{
              flexDirection: "column",
              alignItems: "flex-start",
              justifyContent: "space-between",
              padding: 10,
            }}
          >
            <Text style={styles.header_content}>
              Importance to Your Health:
            </Text>
            <Text style={styles.text_content}>
              {biomarkerInfo[biomarker]["info"]}
            </Text>
          </View>
        </View>
        <View style={styles.card_element}>
          <View
            style={{
              flexDirection: "column",
              alignItems: "flex-start",
              justifyContent: "space-between",
              padding: 10,
            }}
          >
            <Text style={styles.header_content}>Diet Suggestions:</Text>
            <Text style={styles.text_content}>
              {biomarkerInfo[biomarker]["suggestions"]}
            </Text>
          </View>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
};

export default App;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#D3D3D3",
    justifyContent: "center",
    alignItems: "center",
    textAlign: "center",
    padding: 0,
  },
  horizontal: {
    flexDirection: "row",
    alignItems: "flex-end",
    justifyContent: "flex-end",
  },
  heading: {
    color: "#fff",
    fontSize: 20,
    fontWeight: "600",
    marginTop: 30,
    marginBottom: 10,
    textAlign: "center",
  },
  tinyLogo: {
    width: 40,
    height: 40,
  },
  header: {
    color: "#484d52",
    textAlign: "center",
    fontSize: 20,
    fontWeight: "600",
    fontStyle: "italic",
  },
  card_element: {
    padding: 10,
    backgroundColor: "#4895d9",
    borderRadius: 20,
    marginTop: 15,
    shadowOpacity: 0.5,
    shadowOffset: { height: 1 },
  },
  card_element_header: {
    backgroundColor: "#4895d9",
    borderRadius: 30,
    shadowOpacity: 0.5,
    shadowOffset: { height: 1 },
    marginBottom: 15,
  },
  header_content: {
    fontSize: 20,
    color: "white",
    fontWeight: "600",
    marginBottom: 4,
  },
  header_content_top: {
    fontSize: 20,
    color: "white",
    fontWeight: "600",
    marginLeft: 10,
  },
  text_content: {
    fontSize: 16,
    color: "white",
    fontWeight: "300",
  },
});
