import React, { createContext, useState } from "react";
import biomarkerInfoRaw from "../assets/main-screen.json";

// Create two contexts:
// TestDataContext: to query the context state
// TestDataDispatchContext: to mutate the context state
const BiomarkerInfoContext = createContext(undefined);
const BiomarkerInfoDispatchContext = createContext(undefined);

// A "provider" is used to encapsulate only the
// components that needs the state in this context
function BiomarkerInfoProvider({ children }) {
  const biomarkerInfoStringified = JSON.stringify(biomarkerInfoRaw)
  const biomarkerInfoData = JSON.parse(biomarkerInfoStringified)
  const [infoData, setInfoData] = useState(biomarkerInfoData);

  return (
    
    <BiomarkerInfoContext.Provider value={infoData}>
      <BiomarkerInfoDispatchContext.Provider value={setInfoData}>
        {children}
      </BiomarkerInfoDispatchContext.Provider>
    </BiomarkerInfoContext.Provider>
  );
}

export {BiomarkerInfoProvider, BiomarkerInfoContext, BiomarkerInfoDispatchContext}