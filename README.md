Overview

This is a TCP client application built using Qt. The client sends user information (UserID, UserName, Email) to a server using the UserData protocol and displays the server's response.
Features

    Connects to a TCP server on 127.0.0.1:1237.
    Sends serialized user data (UserID, UserName, Email) using the UserData protocol.
    Displays the server's response in a text widget.
    Handles connection errors gracefully.

Requirements

    Qt 5.15+ or Qt 6.x
    C++17 or higher
    A running TCP server listening on port 1237.

Usage

    Launch the Client:
        Build and run the client application.

    Input Data:
        Enter the following details in the input fields:
            UserID
            UserName
            Email

    Send Data:
        Click the Send button to send the user data to the server.

    View Response:
        The server's response will be displayed in the text widget.

Example Interaction

    Input:
        UserID: 12345
        UserName: nghia
        Email: nghia.trinh@gmail.com
    Response (from server):
    Acknowledged by server

Notes

    Ensure the server is running and accessible on 127.0.0.1:1237.
    Any connection errors will be displayed in the UI or via error messages.
