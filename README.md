# IpMatch

> Lightweight IPv4 parser and subnet matcher written in ANSI C — no includes, no dependencies, just logic.

`IpMatch` is a **minimalist and portable library** that allows you to parse, validate, and compare IPv4 addresses with optional CIDR masks (e.g., `192.168.1.1/24`). It is designed to work without standard libraries, making it ideal for embedded environments, kernels, or allocators under full user control.

---

## 📦 Overview

This library allows you to:

- ✅ Validate IPv4 strings (with or without `/mask`)
- 🔄 Convert IPs into 32-bit binary representation
- 🎯 Match IPs against subnets (CIDR notation)
- 💡 Use custom memory allocation (no malloc dependency)
- 📂 Zero includes, fully self-contained

---

## 📐 Struct: `IpMatch`

```c
typedef struct IpMatch_Module {
  short bus;                 // Internal use only
  const char *ip_string;     // Original IP string (not duplicated)
  unsigned int ip_binary;    // Binary IP (e.g. 0xC0A80101)
  short mask;                // Subnet mask length (e.g. 24 for /24)
  unsigned int mask_binary;  // Binary mask (e.g. 0xFFFFFF00)
} IpMatch;
````

> ⚠️ `ip_string` is **not copied** — keep the original string alive.
>
> 🚫 `bus` is reserved for internal use. Do not touch.

---

## 💡 Memory Injection

`IpMatch` avoids built-in allocation. You must provide your own allocator functions:

```c
typedef void *(*_private_type_malloc_IpMatch)(unsigned long size);
typedef void (*_private_type_free_IpMatch)(void *ptr);
```

You can use `malloc`/`free`, but also `arena_alloc`, `kmalloc`, or static buffers.

---

## 🔧 Public API

### `IpMatch *IpMatch_new_ip(const char *raw_ip, _private_type_malloc_IpMatch allocator);`

Parses a raw IPv4 string (with optional `/mask`) and returns a pointer to a new `IpMatch` object.

* `raw_ip`: The input string (`"192.168.0.1/24"` or `"10.0.0.1"`)
* `allocator`: Your custom memory allocator function
* Returns: `IpMatch*` if valid, `NULL` if invalid or allocation failed

```c
IpMatch *ip = IpMatch_new_ip("192.168.1.1/24", malloc);
```

---

### `void IpMatch_free(IpMatch *self, _private_type_free_IpMatch deallocator);`

Frees an `IpMatch` object using the provided free function.

```c
IpMatch_free(ip, free);
```

---

### `short IpMatch_is_ipv4_valid(const char *ip_str, int *octets_out, short *mask_out);`

Validates the format of an IPv4 string with optional `/mask`.

* Returns `1` if valid, `0` if invalid.
* `octets_out`: Optional output for the 4 octets (set to `NULL` if unused)
* `mask_out`: Optional output for the subnet mask (`NULL` if unused)

```c
if (IpMatch_is_ipv4_valid("10.0.0.1/8", NULL, NULL)) {
  // Valid format
}
```

---

### `short IpMatch_is_ip_inside(IpMatch *ref, IpMatch *ip);`

Checks whether `ip` is within the subnet described by `ref`.

* If `ref->mask == 32`, performs exact match.
* Otherwise, applies bitwise mask comparison.

```c
IpMatch *net = IpMatch_new_ip("192.168.0.0/24", malloc);
IpMatch *test = IpMatch_new_ip("192.168.0.42", malloc);

if (IpMatch_is_ip_inside(net, test)) {
  // test is inside 192.168.0.0/24
}

IpMatch_free(net, free);
IpMatch_free(test, free);
```

---

## 🧪 Examples

### ✅ Creating and checking an IP

```c
IpMatch *ip = IpMatch_new_ip("10.1.2.3/16", malloc);

printf("Binary IP: %08X\n", ip->ip_binary);
printf("Binary Mask: %08X\n", ip->mask_binary);

IpMatch_free(ip, free);
```

---

### ❌ Invalid IP format

```c
if (!IpMatch_is_ipv4_valid("256.1.1.1", NULL, NULL)) {
  // Invalid: out of range
}
```

---

### 🔎 Subnet checking

```c
IpMatch *network = IpMatch_new_ip("10.0.0.0/8", malloc);
IpMatch *client  = IpMatch_new_ip("10.123.45.67", malloc);

if (IpMatch_is_ip_inside(network, client)) {
  // IP is within 10.0.0.0/8
}

IpMatch_free(network, free);
IpMatch_free(client, free);
```

### Main

```c
IpMatch *criar_um_ip(const char *ip){

  if(!IpMatch_is_ipv4_valid(ip, NULL, NULL)){
    printf("Not ip valid!!!");
    exit(1);
  }

  IpMatch *ip_criado = IpMatch_new_ip(ip, malloc);
  if(!ip_criado){
    printf("\n\tError internal!!!\n");
    exit(1);
  }

  return ip_criado;
}

int main(){
  printf("\n\tStarted\n");

  const char *ref_str = "8.0.0.0/8";
  const char *ip_str = "8.4.2.1/23";

  IpMatch *ref = criar_um_ip(ref_str);
  IpMatch *ip = criar_um_ip(ip_str);

  printf("\n\tThis iquals? <%s>\n", IpMatch_is_ip_inside(ref, ip)?"TRUE":"FALSE");

  IpMatch_free(ref, free);
  IpMatch_free(ip, free);

  return 0;
}
```

---

## 🧠 Internal Parsing (for advanced use)

### `short Private_IpMatch_parser_ipv4(IpMatch *self);`

Internal function used by `IpMatch_new_ip`. Parses `self->ip_string` into binary fields.

* Returns `1` if parsing succeeds.
* Returns `0` if the string is invalid.

**Not recommended for direct use** unless you manually build `IpMatch` structs.

---

## 🧯 Roadmap

* ✅ IPv4 support with CIDR masks
* 🧪 Embedded-safe design
* 🔒 Memory injection support
* 🌐 Future: IPv6 parsing and matching

---

