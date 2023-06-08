import React, { createContext, useState } from "react";
import bloodTestDataRaw from "../assets/bloodtest.json";

// Create two contexts:
// TestDataContext: to query the context state
// TestDataDispatchContext: to mutate the context state
const TestDataContext = createContext(undefined);
const TestDataDispatchContext = createContext(undefined);

// A "provider" is used to encapsulate only the
// components that needs the state in this context
function TestDataProvider({ children }) {
  const bloodTestDataStringified = JSON.stringify(bloodTestDataRaw)
  const bloodTestData = JSON.parse(bloodTestDataStringified)
  const [testData, setTestData] = useState(bloodTestData);

  return (
    
    <TestDataContext.Provider value={testData}>
      <TestDataDispatchContext.Provider value={setTestData}>
        {children}
      </TestDataDispatchContext.Provider>
    </TestDataContext.Provider>
  );
}

export {TestDataProvider, TestDataContext, TestDataDispatchContext}