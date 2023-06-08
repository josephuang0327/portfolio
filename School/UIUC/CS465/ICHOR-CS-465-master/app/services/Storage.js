import AsyncStorage from '@react-native-async-storage/async-storage';

export const storeData = async (key, value) => {
  try {
    console.log(value)
    await AsyncStorage.setItem(key, value)
  } catch (e) {
    // saving error
  }
}

export const getData = async (key) => {
  try {
    const value = await AsyncStorage.getItem(key)
    if(value !== null) {
      // value previously stored
      // console.log(value)
      // console.log(JSON.parse(value))
      console.log(value)
      return value;
    }
  } catch(e) {
    // error reading value
  }
}
