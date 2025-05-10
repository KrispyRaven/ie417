# Solución Ampliada para Laboratorio 4 - Nuevas Preguntas de Entrevista con Patrones de Diseño

## 1. Preguntas de entrevista con análisis de patrones de diseño

### Pregunta 1: "¿Cómo diseñarías un sistema de notificaciones que pueda enviar mensajes por email, SMS y push notifications?"

**Problema**: Necesitamos un sistema flexible que permita enviar notificaciones a través de múltiples canales, con la posibilidad de añadir nuevos métodos en el futuro sin modificar el código existente.

**Patrón adecuado**: Bridge

**Justificación**:
- Bridge separa la abstracción (notificación) de su implementación (canal de envío)
- Permite variar independientemente los tipos de notificaciones y los métodos de envío
- Fácil de extender con nuevos canales de notificación

**Implementación en Python**:
```python
from abc import ABC, abstractmethod

# Implementación
class NotificationSender(ABC):
    @abstractmethod
    def send(self, message: str, recipient: str):
        pass

class EmailSender(NotificationSender):
    def send(self, message: str, recipient: str):
        print(f"Enviando email a {recipient}: {message}")

class SMSSender(NotificationSender):
    def send(self, message: str, recipient: str):
        print(f"Enviando SMS a {recipient}: {message}")

class PushSender(NotificationSender):
    def send(self, message: str, recipient: str):
        print(f"Enviando push a {recipient}: {message}")

# Abstracción
class Notification:
    def __init__(self, sender: NotificationSender):
        self.sender = sender

    def send(self, recipient: str, message: str):
        self.sender.send(message, recipient)

# Notificaciones especializadas
class AlertNotification(Notification):
    def send_alert(self, recipient: str):
        self.send(recipient, "ALERTA: Situación crítica!")

# Uso:
email_notification = Notification(EmailSender())
email_notification.send("usuario@example.com", "Mensaje importante")

sms_alert = AlertNotification(SMSSender())
sms_alert.send_alert("+123456789")
```

### Pregunta 2: "¿Cómo implementarías un sistema de procesamiento de pedidos con diferentes etapas (validación, pago, envío)?"

**Problema**: Necesitamos manejar pedidos que pasan por una serie de pasos secuenciales, donde cada paso debe ejecutarse solo si el anterior fue exitoso.

**Patrón adecuado**: Chain of Responsibility

**Justificación**:
- Permite encadenar los pasos de procesamiento
- Cada paso puede decidir si procesa la solicitud o la pasa al siguiente
- Fácil de modificar la cadena o añadir nuevos pasos

**Implementación en Python**:
```python
from abc import ABC, abstractmethod

class Order:
    def __init__(self, items: list, user_id: str):
        self.items = items
        self.user_id = user_id
        self.is_valid = False
        self.is_paid = False
        self.is_shipped = False

class Handler(ABC):
    def __init__(self):
        self.next_handler = None

    def set_next(self, handler):
        self.next_handler = handler
        return handler

    @abstractmethod
    def handle(self, order: Order):
        pass

class ValidationHandler(Handler):
    def handle(self, order: Order):
        print("Validando orden...")
        if len(order.items) > 0:
            order.is_valid = True
            print("Validación exitosa")
            return self.next_handler.handle(order) if self.next_handler else None
        print("Validación fallida: carrito vacío")

class PaymentHandler(Handler):
    def handle(self, order: Order):
        if order.is_valid:
            print("Procesando pago...")
            order.is_paid = True
            print("Pago completado")
            return self.next_handler.handle(order) if self.next_handler else None
        print("Pago fallido: orden no válida")

class ShippingHandler(Handler):
    def handle(self, order: Order):
        if order.is_paid:
            print("Preparando envío...")
            order.is_shipped = True
            print("Envío programado")
            return self.next_handler.handle(order) if self.next_handler else None
        print("Envío fallido: pago no completado")

# Uso:
order = Order(["libro", "laptop"], "user123")

validator = ValidationHandler()
payment = PaymentHandler()
shipping = ShippingHandler()

validator.set_next(payment).set_next(shipping)

validator.handle(order)
```

### Pregunta 3: "¿Cómo diseñarías un sistema de suscripciones donde los usuarios puedan seguir eventos de otros usuarios?"

**Problema**: Necesitamos implementar un sistema donde los usuarios puedan suscribirse a las actualizaciones de otros usuarios y recibir notificaciones cuando ocurran eventos importantes.

**Patrón adecuado**: Observer

**Justificación**:
- Observer permite que objetos (observadores) se suscriban a eventos de otro objeto (sujeto)
- El sujeto notifica automáticamente a todos los observadores cuando ocurre un cambio
- Bajo acoplamiento entre el sujeto y los observadores

**Implementación en Python**:
```python
from abc import ABC, abstractmethod

class Subject(ABC):
    @abstractmethod
    def attach(self, observer):
        pass

    @abstractmethod
    def detach(self, observer):
        pass

    @abstractmethod
    def notify(self):
        pass

class User(Subject):
    def __init__(self, name: str):
        self.name = name
        self._followers = []
        self._last_post = None

    def attach(self, observer):
        if observer not in self._followers:
            self._followers.append(observer)

    def detach(self, observer):
        self._followers.remove(observer)

    def notify(self):
        for follower in self._followers:
            follower.update(self)

    def post_update(self, message: str):
        self._last_post = message
        print(f"{self.name} publicó: {message}")
        self.notify()

class Follower:
    def __init__(self, name: str):
        self.name = name

    def update(self, subject: User):
        print(f"{self.name} recibió notificación de {subject.name}: {subject._last_post}")

# Uso:
user1 = User("Ana")
follower1 = Follower("Carlos")
follower2 = Follower("Diana")

user1.attach(follower1)
user1.attach(follower2)

user1.post_update("Acabo de publicar un nuevo artículo!")

user1.detach(follower2)
user1.post_update("Nuevo proyecto en GitHub!")
```

## 2. Reflexión adicional sobre patrones de diseño

Al analizar estas nuevas preguntas, profundicé en los siguientes aprendizajes:

1. **Bridge vs Strategy**: Mientras Strategy se enfoca en comportamientos intercambiables, Bridge separa abstracción de implementación para sistemas más complejos con múltiples dimensiones de variación.

2. **Chain of Responsibility** es ideal para pipelines de procesamiento donde el orden de los pasos puede variar o necesitamos flexibilidad para modificar la secuencia.

3. **Observer** es fundamental en sistemas modernos que manejan eventos en tiempo real, como notificaciones o actualizaciones en redes sociales.

4. La elección del patrón depende no solo del problema inmediato, sino también de los requisitos futuros de escalabilidad y mantenimiento.

5. En entrevistas técnicas, es valioso mencionar alternativas y por qué se descartaron (ej: para el sistema de pedidos, State también sería posible pero menos adecuado).

6. Los patrones a menudo reflejan principios SOLID:
   - Bridge y Observer siguen el Principio de Inversión de Dependencias
   - Chain of Responsibility sigue el Principio de Responsabilidad Única

Esta experiencia me demostró cómo los patrones proporcionan un lenguaje común para discutir soluciones arquitectónicas y cómo su aplicación adecuada puede simplificar significativamente sistemas complejos.