if [ ! -f ./backend/.env ]; then
    touch ./backend/.env
    echo "LOGIN=${LOGIN}" >> ./backend/.env
    echo "DATABASE_URL=${DATABASE_URL}" >> ./backend/.env
    echo "CLIENT_ID=${CLIENT_ID}" >> ./backend/.env
    echo "CLIENT_SECRET=${CLIENT_SECRET}" >> ./backend/.env
    echo "JWT_KEY=${JWT_KEY}" >> ./backend/.env
    echo "export const login = async () => {window.location.href = \""${REDIRECT}"\"}" >> ./frontend/src/views/Login/login.42api.tsx
    sleep 2
    exit 0
fi

