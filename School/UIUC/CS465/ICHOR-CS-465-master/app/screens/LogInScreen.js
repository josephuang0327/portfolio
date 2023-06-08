import React from "react";
import {
  StyleSheet,
  ImageBackground,
  Dimensions,
  KeyboardAvoidingView,
  View,
  Pressable,
  Text,
  TextInput,
  Button
} from "react-native";
import { CheckBox } from 'react-native-elements'
import { AntDesign } from '@expo/vector-icons';
import { MaterialIcons } from '@expo/vector-icons';

const { width, height } = Dimensions.get("screen");

class Register extends React.Component {
  render() {

    return (
      
      <View flex style={styles.background}>
          <View safe flex middle style = {styles.outer}>
            <View style={styles.registerContainer}>
              <View flex={0.25} middle style={styles.socialConnect}>
                <View marginTop={40}>
                  <Text style={{color: "#fff", fontWeight: "bold", fontSize: 15}}>
                    SIGN IN WITH
                  </Text>
                </View>
                
                <View  style={{ marginTop: 30, flex: 1,
                                flexDirection: 'row',
                                justifyContent: 'space-between' }}>
                <Pressable style={{...styles.socialButtons, marginRight:30}} onPress={() => navigation.navigate("App")}>
                <View style={{flexDirection: "row"}}>
                  <MaterialIcons 
                  name="facebook" 
                  size={16} 
                  color="white" 
                  style={{ marginRight: 5 }}/>
                  <Text style={styles.socialTextButtons}>FaceBook</Text>
                </View>
                </Pressable>

                <Pressable style={{...styles.socialButtons}} onPress={() => navigation.navigate("App")}>
                <View style={{flexDirection: "row"}}>
                <AntDesign 
                  name="google" 
                  size={16} 
                  color="white" 
                  style={{ marginRight: 5 }}/>
                  <Text style={styles.socialTextButtons}>Google</Text>
                </View>
                </Pressable>
                </View>
              </View>
              <View flex>
                <View flex={0.12} middle justifyContent= 'center' alignItems= 'center'>
                  <Text style={{color: "#fff", fontWeight: "bold", fontSize: 15}}>
                    SIGN IN WITH EMAIL
                  </Text>
                </View>
                <View flex center>
                  <KeyboardAvoidingView
                    style={{ flex: 1 }}
                    behavior="padding"
                    enabled
                  >
                    <View width={width * 0.8} style={{ marginBottom: 30, flexDirection:"row" }}>
                    <MaterialIcons 
                          name="email" 
                          size={16} 
                          color="white" 
                          style={{ marginTop: 15, marginRight: 5 }}/>
                      <TextInput style={styles.input}
                        placeholder="Email"
                          />
                    </View>
                    <View width={width * 0.8} style={{ marginBottom: 30, flexDirection:"row" }}>
                    <MaterialIcons 
                          name="lock" 
                          size={16} 
                          color="white" 
                          style={{ marginTop: 15, marginRight: 5 }}/>
                      <TextInput style={styles.input}
                        password
                        placeholder="Password"
                          />

                    </View>
                    <View width={width * 0.8}>
                    <CheckBox 
                      title='I agree with the policy of information usage'

                    />
                      <Button
                        title = "Privacy Policy"
                        style={{ width: 100 }}
                        color="transparent"
                        textStyle={{
                          color: "#88a7f2",
                          fontSize: 14
                        }}
                      >
                        
                      </Button>
                    </View>
                    <View middle justifyContent='center' alignItems='center'>
                      
                      <Pressable  style={styles.button}
                      onPress={() => this.props.navigation.navigate("Main")} >
                        <Text bold style={styles.baseText}>
                          Login
                        </Text>
                      </Pressable>
                      <Pressable style={styles.button} 
                      onPress={() => this.props.navigation.navigate("Main")} >
                        <Text bold style={styles.baseText}>
                          Create Account
                        </Text>
                      </Pressable>

                      
                    </View>
                  </KeyboardAvoidingView>
                </View>
              </View>
            </View>
          </View>
       
      </View>
    );
  }
}

const styles = StyleSheet.create({
  background: {
    backgroundColor: '#D3D3D3'
  },
  button: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 12,
    paddingHorizontal: 20,
    borderRadius: 10,
    elevation: 3,
    backgroundColor: '#484d52',
    marginTop: 25,
    width: width*0.4
  },
  input: {
    height: 40,
    margin: 12,
    borderWidth: 1,
    padding: 10,
    flex: 1,
    backgroundColor: "#fff"
  },
  baseText: {
    size: 14,
    fontWeight: "bold",
    color : 'white'
  },
  outer:{
    justifyContent: 'center',
    alignItems: 'center'
  },
  registerContainer: {
    justifyContent: 'center',
    alignItems: 'center',
    width: width * 0.9,
    height: height * 0.875,
    backgroundColor: "#4895d9",
    borderRadius: 4,
    shadowColor: "black",
    shadowOffset: {
      width: 0,
      height: 4
    },
    shadowRadius: 8,
    shadowOpacity: 0.1,
    elevation: 1,
    overflow: "hidden"
  },
  socialConnect: {
    justifyContent: 'center',
    alignItems: 'center',
    alignSelf: 'stretch',
    backgroundColor: "#4895d9",
    borderBottomWidth: 1,
    borderColor: "#8898AA"
  },
  socialButtons: {
    flexDirection: 'row',
    justifyContent: 'center',
    alignItems: 'center',
    width: "40%",
    height: 40,
    backgroundColor: "#484d52",
    shadowColor: "black",
    shadowOffset: {
      width: 0,
      height: 4
    },
    borderRadius: 10,
    shadowRadius: 8,
    shadowOpacity: 0.1,
    elevation: 1
  },
  socialTextButtons: {
    color: "#fff",
    fontWeight: "800",
    fontSize: 14
  },
  inputIcons: {
    marginRight: 12
  },
  passwordCheck: {
    paddingLeft: 15,
    paddingTop: 13,
    paddingBottom: 30
  },
  createButton: {
    width: width * 0.5,
    marginTop: 25
  }
});

export default Register;