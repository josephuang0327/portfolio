import React, { createContext, useState } from "react";

// Create two contexts:
// TestDataContext: to query the context state
// TestDataDispatchContext: to mutate the context state
const ImportVisitedContext = createContext(undefined);
const ImportVisitedDispatchContext = createContext(undefined);

// A "provider" is used to encapsulate only the
// components that needs the state in this context
function ImportVisitedProvider({ children }) {
  const [importVisited, setImportVisited] = useState(false);

  return (
    <ImportVisitedContext.Provider value={importVisited}>
      <ImportVisitedDispatchContext.Provider value={setImportVisited}>
        {children}
      </ImportVisitedDispatchContext.Provider>
    </ImportVisitedContext.Provider>
  );
}

export {ImportVisitedProvider, ImportVisitedContext, ImportVisitedDispatchContext}