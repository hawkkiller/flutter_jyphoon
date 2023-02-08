//
//  Initialization.swift
//  jc
//
//  Created by Михаил on 08.02.2023.
//

import Foundation

class Initialization {
    public func setAppKey(key: String) {
        JCRoom.APP_KEY = key
    }
    
    public func setServerAddress(serverAddress: String) {
        JCRoom.SERVER_ADDRESS = serverAddress
    }
    
    public func initialize() -> Bool {
       return JCRoom.shared.initialize()
    }
}
