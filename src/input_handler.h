

    int handle_keys(sf::Event sfEvent, sf::Keyboard key){
        
        if(key.isKeyPressed(key.Escape)) return 0;
        if(key.isKeyPressed(key.W)) return 0;
        if(key.isKeyPressed(key.A)) return 0;
        if(key.isKeyPressed(key.S)) return 0;
        if(key.isKeyPressed(key.D)) return 0;
        if(key.isKeyPressed(key.Space)) return 0;
        
        if(sfEvent.type == sf::Event::KeyReleased){
            if (sfEvent.key.code == key.Enter 
                && key.isKeyPressed(key.LAlt)) return 1; 

            if(sfEvent.key.code == key.C) return 1;
            if(sfEvent.key.code == key.W) return 1;
            if(sfEvent.key.code == key.A) return 1;
            if(sfEvent.key.code == key.S) return 1;
            if(sfEvent.key.code == key.D) return 1;
            if(sfEvent.key.code == key.Space) return 1;
        }
        return 2;

    };


    int handle_mouse(sf::Event sfEvent, sf::Mouse mouse){
        if(mouse.isButtonPressed(mouse.Right)) return 1;
        if (sfEvent.type == sf::Event::MouseButtonReleased)
            if (sfEvent.mouseButton.button == mouse.Right)
                return 2;
        return 0;
    };
