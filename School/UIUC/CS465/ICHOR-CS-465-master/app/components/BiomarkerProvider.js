import React, { createContext, useState } from "react";

// Create two contexts:
// BiomarkerContext: to query the context state
// BiomarkerDispatchContext: to mutate the context state
const BiomarkerContext = createContext(undefined);
const BiomarkerDispatchContext = createContext(undefined)


// A "provider" is used to encapsulate only the
// components that needs the state in this context
function BiomarkerProvider({ children }) {

  const [currentBiomarker, setCurrentBiomarker] = useState({});

  return (
    <BiomarkerContext.Provider value={currentBiomarker}>
      <BiomarkerDispatchContext.Provider value={setCurrentBiomarker}>
        {children}
      </BiomarkerDispatchContext.Provider>
    </BiomarkerContext.Provider>
  );
}

export {BiomarkerProvider, BiomarkerContext, BiomarkerDispatchContext}